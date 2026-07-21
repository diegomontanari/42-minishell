#include "minishell.h"

/*
** new_token
**
** This function creates a new token structure.
** - Allocate memory for a new t_token.
** - If allocation fails, return NULL.
** - Set token->value to a duplicate of the input value string.
**     * If the duplicate fails, free the token and return NULL.
** - Set token->type to the specified type.
** - Set token->next to NULL (it will be linked later).
** - Return the newly created token.
*/
t_token	*new_token(char *value, int type, int is_quoted)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->is_quoted = is_quoted;
	token->heredoc_fd = -1;
	token->next = NULL;
	return (token);
}

/*
** get_full_line
**
** This function builds a complete input string, handling cases
** where quotes are left unclosed.
** - Start by duplicating the initial input.
** - While unclosed quotes exist in the current string:
**     * Prompt the user with "> " and read another line.
**     * If the user provides no line (NULL), stop reading.
**     * Append the new line to the current input string using
**       append_line_to_input().
**     * If appending fails, return NULL.
** - Return the final complete input string.
*/
char	*get_full_line(char *initial_input)
{
	if (!initial_input)
		return (NULL);
	return (ft_strdup(initial_input));
}
