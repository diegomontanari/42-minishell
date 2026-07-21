#include "minishell.h"

/*
** restore_redirection
**
** This function restores the original standard input/output after
** a redirection.
*/
void	restore_redirection(t_shell *shell)
{
	if ((shell->redirect_type == TK_OUT
			|| shell->redirect_type == TK_APPEND)
		&& shell->stdout_backup >= 0)
	{
		if (dup2(shell->stdout_backup, 1) == -1)
			perror("dup2");
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
	restore_input_redirection(shell);
	shell->redirect_type = 0;
}

/*
** apply_input_redirection
**
** This function applies input redirection for a command.
*/
int	apply_input_redirection(int input_fd, t_shell *shell)
{
	int	saved_stdin;

	saved_stdin = dup(0);
	if (saved_stdin == -1)
	{
		perror("minishell: dup");
		close(input_fd);
		return (-1);
	}
	if (dup2(input_fd, 0) == -1)
	{
		perror("minishell: dup2");
		close(input_fd);
		close(saved_stdin);
		return (-1);
	}
	close(input_fd);
	shell->stdin_backup = saved_stdin;
	return (0);
}

/*
** handle_single_input_redirect
**
** This function handles a single input redirection token.
*/
int	handle_single_input_redirect(t_token *curr, t_shell *shell, int *input_fd)
{
	int	new_input_fd;

	if (valid_syntax_token(curr) == -1)
	{
		if (*input_fd != -1)
			close(*input_fd);
		return (-1);
	}
	new_input_fd = open_input_file(curr, shell);
	if (new_input_fd < 0)
	{
		if (*input_fd != -1)
			close(*input_fd);
		return (new_input_fd);
	}
	update_input_fd(input_fd, new_input_fd);
	return (0);
}

/*
** setup_sigpipe_handling
**
** This function configures signal handling for SIGPIPE.
*/
void	setup_sigpipe_handling(void)
{
	signal(SIGPIPE, SIG_DFL);
}
