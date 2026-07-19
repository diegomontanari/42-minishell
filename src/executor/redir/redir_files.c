#include "minishell.h"

/*
** open_input_file
**
** This function opens the file specified for input redirection.
*/
int	open_input_file(t_token *curr, t_shell *shell)
{
	char	*filename;

	filename = curr->next->value;
	return (open_file_by_type(filename, curr->type, shell));
}

/*
** open_output_file
**
** This function opens an output file for redirection.
*/
int	open_output_file(t_token *curr, char **filename)
{
	int	flags;
	int	new_fd;

	if (curr->next == NULL || curr->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (-1);
	}
	*filename = curr->next->value;
	if (curr->type == TK_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	new_fd = open(*filename, flags, 0644);
	if (new_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(*filename);
		return (-1);
	}
	return (new_fd);
}

/*
** handle_new_output_fd
**
** This helper function manages a new output file descriptor.
*/
int	handle_new_output_fd(int new_fd, int *file_fd,
								t_shell *shell, t_token *curr)
{
	if (new_fd == -1)
	{
		if (*file_fd != -1)
			close(*file_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	if (*file_fd != -1)
		close(*file_fd);
	*file_fd = new_fd;
	shell->redirect_type = curr->type;
	return (0);
}
