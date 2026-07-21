#include "minishell.h"

/*
** process_heredoc_line
**
** This helper function processes a single line in a heredoc.
** If the delimiter was quoted (e.g. << 'EOF'), variable
** expansion must not happen inside the body, matching bash.
*/
static int	process_heredoc_line(int write_fd, char *line,
			int is_quoted, t_shell *shell)
{
	char	*expanded_line;

	if (is_quoted)
		expanded_line = ft_strdup(line);
	else
		expanded_line = expand_variables(line, shell);
	if (!expanded_line)
		return (-1);
	if (write_heredoc_data(write_fd, expanded_line,
			ft_strlen(expanded_line)) == -1
		|| write_heredoc_data(write_fd, "\n", 1) == -1)
	{
		perror("minishell: write");
		free(expanded_line);
		return (-1);
	}
	free(expanded_line);
	return (0);
}

static void	print_heredoc_eof_warning(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file\n", 2);
}

/*
** read_heredoc_lines
**
** This function continuously reads user input until the heredoc
** delimiter is reached.
*/
static int	read_heredoc_lines(int write_fd, char *delimiter,
				int is_quoted, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_heredoc_eof_warning();
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(write_fd, line, is_quoted, shell) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

static void	run_heredoc_child(int file_fd, char *delimiter,
					int is_quoted, t_shell *shell)
{
	int	result;

	setup_signals_child();
	signal(SIGQUIT, SIG_IGN);
	result = read_heredoc_lines(file_fd, delimiter, is_quoted, shell);
	close(file_fd);
	full_shell_cleanup(shell);
	if (result == -1)
		exit(1);
	exit(0);
}

/*
** create_heredoc_pipe
**
** This function creates a pipe and fills it with heredoc input.
*/
int	create_heredoc_pipe(char *delimiter, int is_quoted, t_shell *shell)
{
	int		file_fd;
	pid_t	pid;
	char	*path;

	file_fd = open_heredoc_temp(&path);
	if (file_fd == -1)
	{
		perror("minishell: heredoc");
		return (-1);
	}
	setup_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		close_heredoc_temp(path, file_fd, 0);
		setup_signals_interactive();
		return (-1);
	}
	if (pid == 0)
	{
		free(path);
		run_heredoc_child(file_fd, delimiter, is_quoted, shell);
	}
	return (finish_heredoc_file(pid, file_fd, path, shell));
}
