#include "minishell.h"

/*
** is_redir_target
**
** This function checks if a token is the target of an input
** redirection.
** - Iterate through the token list until reaching 'curr',
**   keeping track of the previous token.
** - If the previous token exists and its type is TK_IN ('<')
**   or TK_HEREDOC ('<<'), then 'curr' is a redirection target.
** - Return 1 if curr is an input redirection target,
**   otherwise return 0.
*/
int	is_redir_target(t_token *head, t_token *target)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = head;
	while (curr && curr != target)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev && (prev->type == TK_IN || prev->type == TK_HEREDOC
			|| prev->type == TK_OUT || prev->type == TK_APPEND))
		return (1);
	return (0);
}

/*
** is_redirection_file
**
** This function checks if a token represents a file used in a
** redirection.
** - If target is the first token in the list, return 0 because it
**   cannot be a redirection target.
** - Otherwise, find the token immediately before target.
** - If the previous token type is TK_OUT ('>'), TK_APPEND ('>>'),
**   TK_IN ('<'), or TK_HEREDOC ('<<'), then target is the file
**   associated with that redirection.
** - Return 1 if curr is a redirection file, otherwise 0.
*/
int	is_redirection_file(t_token *head, t_token *target)
{
	t_token	*prev;

	if (target == head)
		return (0);
	prev = head;
	while (prev->next && prev->next != target)
		prev = prev->next;
	if (prev && (prev->type == TK_OUT || prev->type == TK_APPEND
			|| prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	return (0);
}

/*
** args_fill_array
**
** This function copies word tokens into a string array for
** command execution.
** - Iterate through the token list while filling up to
**   argc elements in args.
** - For each TK_WORD token:
**     * If it is not a redirection file (checked with
**       is_redirection_file()), duplicate its value and store
**       it in the args array.
**     * If duplication fails, free the args array and return NULL.
** - Continue until all valid arguments are copied.
** - Return the filled args array.
*/
static int	add_arg_if_valid(t_token *head, t_token *curr, char **args, int *i)
{
	if (curr->type == TK_WORD && !is_redirection_file(head, curr))
	{
		if (curr->is_quoted || (curr->value && curr->value[0] != '\0'))
		{
			args[*i] = ft_strdup(curr->value);
			if (!args[*i])
			{
				free_str_array(args);
				return (-1);
			}
			(*i)++;
		}
	}
	return (0);
}

char	**args_fill_array(t_token *head, char **args, int argc)
{
	t_token	*curr;
	int		i;

	curr = head;
	i = 0;
	while (curr && i < argc)
	{
		if (add_arg_if_valid(head, curr, args, &i) == -1)
			return (NULL);
		curr = curr->next;
	}
	return (args);
}

/*
** args_extract_from_tokens
**
** This function builds an array of command arguments excluding
** redirection files.
** - Count the number of non-redirection word tokens using
**   count_valid_args().
** - If no valid words are found, return NULL.
** - Allocate an array of strings with space for argc + 1
**   (extra slot for the NULL terminator).
** - If allocation fails, return NULL.
** - Fill the array by copying tokens with args_fill_array().
** - If copying fails, return NULL.
** - Set the last element to NULL and return the args array.
*/
char	**args_extract_from_tokens(t_token *head)
{
	int		argc;
	char	**args;

	argc = count_valid_args(head);
	if (argc == 0)
		return (NULL);
	args = ft_calloc(argc + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args = args_fill_array(head, args, argc);
	if (!args)
		return (NULL);
	args[argc] = NULL;
	return (args);
}
