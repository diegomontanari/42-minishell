#include "minishell.h"

/*
** open_regular_file
**
** This function opens a regular file based on the type of
** redirection token.
*/
int	open_regular_file(char *filename, int token_type)
{
	int	fd;
	int	flags;

	if (token_type == TK_IN)
		fd = open(filename, O_RDONLY);
	else if (token_type == TK_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(filename, flags, 0644);
	}
	else if (token_type == TK_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(filename, flags, 0644);
	}
	else
		return (-1);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(filename);
	}
	return (fd);
}

/*
** open_file_by_type
**
** This function opens a file depending on the redirection type.
*/
int	open_file_by_type(char *filename, int token_type,
			int is_quoted, t_shell *shell)
{
	if (token_type == TK_HEREDOC)
		return (create_heredoc_pipe(filename, is_quoted, shell));
	return (open_regular_file(filename, token_type));
}

/*
** has_input_redirection
**
** This function checks if a command contains any input
** redirection tokens.
*/
int	has_input_redirection(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
			return (1);
		curr = curr->next;
	}
	return (0);
}

/*
** has_output_redirection
**
** This function checks if a command contains any output
** redirection tokens.
*/
int	has_output_redirection(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
			return (1);
		curr = curr->next;
	}
	return (0);
}
