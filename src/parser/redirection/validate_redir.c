#include "minishell.h"

/*
** valid_syntax_token
**
** This function checks if a redirection token is followed by
** a valid target.
** - If the current token has no next token, or if the next
**   token is not of type TK_WORD, the syntax is invalid.
** - In that case, print a syntax error message to stderr and
**   return -1.
** - Otherwise, return 0 to indicate valid syntax.
*/
int	valid_syntax_token(t_token *token)
{
	if (token->next == NULL || token->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (-1);
	}
	return (0);
}

/*
** validate_heredoc_redirections
**
** This function validates all heredoc redirections ("<<")
** in the token list.
** - Iterate through each token in the list.
** - If the token type is TK_HEREDOC ("<<"):
**     * Call valid_syntax_token() to ensure the heredoc
**       is followed by a valid word token (the delimiter).
**     * If the syntax is invalid, return -1.
** - If all heredoc tokens are valid, return 0.
*/
int	validate_heredoc_redirections(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (curr->type == TK_HEREDOC)
		{
			if (valid_syntax_token(curr) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}

/*
** check_file_access
**
** This helper function checks if a file can be opened
** in read-only mode.
** - Try to open the file with O_RDONLY.
** - If open fails, print an error message using perror()
**   with "minishell" as the prefix and return -1.
** - If open succeeds, immediately close the file descriptor
**   and return 0.
*/
static int	check_file_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(filename);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
** validate_in_redirections
**
** This function validates all input redirections ("<") in the
** token list.
** - Iterate through each token in the list.
** - If the token type is TK_IN ("<"):
**     * Call check_redirection_syntax() to ensure the syntax
**       is valid (must be followed by a word).
**     * If syntax is invalid, return -1.
**     * Call check_file_access() on the next token (filename)
**       to check if the file can be opened for reading.
**     * If the file check fails, return -1.
** - If all input redirections are valid, return 0.
*/
int	validate_in_redirections(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (curr->type == TK_IN)
		{
			if (valid_syntax_token(curr) == -1)
				return (-1);
			if (check_file_access(curr->next->value) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}

/*
** valid_redirections
**
** This function validates all input-related redirections in
** the token list.
** - First, call validate_in_redirections() to check "<" tokens:
**     * Ensures they are followed by a valid word token.
**     * Ensures the target file can be opened for reading.
** - Then, call validate_heredoc_redirections() to check "<<" tokens:
**     * Ensures they are followed by a valid word token
**       (the heredoc delimiter).
** - If either validation fails, return -1.
** - If all checks succeed, return 0.
*/	
int	valid_redirections(t_token *head)
{
	if (validate_in_redirections(head) == -1)
		return (-1);
	if (validate_heredoc_redirections(head) == -1)
		return (-1);
	return (0);
}
