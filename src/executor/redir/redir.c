/* ************************************************************************** */
/*                                                                            */
/*   redir.c                                                                  */
/*                                                                            */
/*   Applies redirections from a command's redir list.                        */
/*   Each redirection opens a file and replaces stdin or stdout via dup2.     */
/*   Heredoc (<<) is handled via a pipe filled by heredoc.c.                  */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Opens the file for input redirection (<). */
static int	open_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file);
	}
	return (fd);
}

/* Opens the file for output redirection (> or >>). */
static int	open_redir_out(char *file, t_redir_type type)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (type == REDIR_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file);
	}
	return (fd);
}

/* Resolves the fd for any redirection type. */
static int	get_redir_fd(t_redir *redir, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		return (open_redir_in(redir->file));
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (open_redir_out(redir->file, redir->type));
	if (redir->type == REDIR_HEREDOC)
		return (handle_heredoc(redir->file, shell));
	return (-1);
}

/*
 * Walks the redir list and applies each one in order.
 * Stops on first failure and sets exit status to 1.
 */
void	apply_redirs(t_redir *redirs, t_shell *shell)
{
	int	fd;
	int	target;

	while (redirs)
	{
		fd = get_redir_fd(redirs, shell);
		if (fd == -1)
		{
			shell->exit_status = 1;
			return ;
		}
		if (redirs->type == REDIR_IN || redirs->type == REDIR_HEREDOC)
			target = STDIN_FILENO;
		else
			target = STDOUT_FILENO;
		dup2(fd, target);
		close(fd);
		redirs = redirs->next;
	}
}
