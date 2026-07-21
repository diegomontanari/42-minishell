#include "minishell.h"

static char	*make_heredoc_path(int index)
{
	char	*number;
	char	*path;

	number = ft_itoa(index);
	if (!number)
		return (NULL);
	path = ft_strjoin("/tmp/.minishell_heredoc_", number);
	free(number);
	return (path);
}

int	open_heredoc_temp(char **path)
{
	int	fd;
	int	index;

	index = 0;
	while (index < INT_MAX)
	{
		*path = make_heredoc_path(index++);
		if (!*path)
			return (-1);
		fd = open(*path, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
			return (fd);
		free(*path);
		*path = NULL;
		if (errno != EEXIST)
			return (-1);
	}
	return (-1);
}

int	close_heredoc_temp(char *path, int fd, int reopen_file)
{
	int	read_fd;

	close(fd);
	read_fd = -1;
	if (reopen_file)
		read_fd = open(path, O_RDONLY);
	unlink(path);
	free(path);
	return (read_fd);
}

int	finish_heredoc_file(pid_t pid, int fd, char *path, t_shell *shell)
{
	int	status;
	int	read_fd;

	if (waitpid(pid, &status, 0) == -1)
	{
		shell->exit_status = 1;
		setup_signals_interactive();
		return (close_heredoc_temp(path, fd, 0), -1);
	}
	setup_signals_interactive();
	if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		close_heredoc_temp(path, fd, 0);
		return (-2);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (close_heredoc_temp(path, fd, 0), -1);
	read_fd = close_heredoc_temp(path, fd, 1);
	if (read_fd == -1)
		shell->exit_status = 1;
	return (read_fd);
}

int	write_heredoc_data(int fd, char *data, size_t len)
{
	size_t	written;
	ssize_t	result;

	written = 0;
	while (written < len)
	{
		result = write(fd, data + written, len - written);
		if (result <= 0)
			return (-1);
		written += (size_t)result;
	}
	return (0);
}
