#include "minishell.h"

/*
** handle_input_redirection_with_tokens
**
** This function processes all input redirection tokens in a
** command.
*/
int	handle_input_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
	t_token		*curr;
	int			input_fd;

	curr = tokens;
	input_fd = -1;
	while (curr != NULL)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
		{
			if (handle_single_input_redirect(curr, shell, &input_fd) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	if (input_fd != -1)
		return (apply_input_redirection(input_fd, shell));
	return (0);
}

/*
** handle_output_redirection_token
**
** This function processes all output redirection tokens.
*/
int	handle_output_redirection_token(t_token *tokens, t_shell *shell)
{
	t_token	*curr;
	int		file_fd;
	char	*filename;
	int		new_fd;

	curr = tokens;
	file_fd = -1;
	while (curr != NULL)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
		{
			new_fd = open_output_file(curr, &filename);
			if (handle_new_output_fd(new_fd, &file_fd, shell, curr) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	if (setup_output_redirection(file_fd, shell) == -1)
		return (-1);
	return (0);
}

/*
** handle_redirection_with_tokens
**
** This function processes all input and output redirections
** defined in a token list.
*/
static int	process_redirection_loop(t_token *tokens, t_shell *shell,
				int *input_fd, int *output_fd)
{
	t_token	*curr;
	char	*filename;

	curr = tokens;
	while (curr != NULL)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
		{
			if (handle_single_input_redirect(curr, shell, input_fd) == -1)
				return (-1);
		}
		else if (curr->type == TK_OUT || curr->type == TK_APPEND)
		{
			filename = NULL;
			if (handle_new_output_fd(open_output_file(curr, &filename),
					output_fd, shell, curr) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}

int	handle_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
	int		input_fd;
	int		output_fd;

	input_fd = -1;
	output_fd = -1;
	if (process_redirection_loop(tokens, shell, &input_fd, &output_fd) == -1)
		return (-1);
	if (input_fd != -1 && apply_input_redirection(input_fd, shell) == -1)
		return (-1);
	if (output_fd != -1 && setup_output_redirection(output_fd, shell) == -1)
		return (-1);
	return (0);
}
