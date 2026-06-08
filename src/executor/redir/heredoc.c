/* ************************************************************************** */
/*                                                                            */
/*   heredoc.c                                                                */
/*                                                                            */
/*   Reads input line by line until the delimiter is found, writes it to      */
/*   a pipe, and returns the read end so it can replace stdin.                */
/*   Variables are expanded in heredoc lines (bash behaviour).                */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Reads lines until delimiter, writes them to write_fd. */
static void	read_heredoc_lines(int write_fd, char *delim,
		t_shell *shell)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_str(line, shell);
		ft_putendl_fd(expanded, write_fd);
		free(line);
		free(expanded);
	}
}

/*
 * Creates a pipe, fills the write end with heredoc content,
 * returns the read end fd so it can replace stdin.
 * Returns -1 on pipe failure.
 */
int	handle_heredoc(char *delim, t_shell *shell)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	read_heredoc_lines(pfd[1], delim, shell);
	close(pfd[1]);
	return (pfd[0]);
}
