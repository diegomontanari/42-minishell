/* ************************************************************************** */
/*                                                                            */
/*   tokenizer.c                                                              */
/*                                                                            */
/*   Splits the raw input string into a linked list of typed tokens.         */
/*   tokenize      : main entry point, drives the character loop.            */
/*   new_token     : allocates a single token node.                          */
/*   add_token_back: appends a token to the end of the list.                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Allocates a new t_token, copies value onto the heap, sets type.
 * Returns NULL if malloc fails; no partial allocation is left alive.
 */
t_token	*new_token(char *value, t_token_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value);
	if (!tok->value)
	{
		free(tok);
		return (NULL);
	}
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

/*
 * Appends a token to the end of the linked list.
 * If the list is empty, the new token becomes the head.
 */
static void	add_token_back(t_token **list, t_token *tok)
{
	t_token	*cur;

	if (!*list)
	{
		*list = tok;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = tok;
}

/*
 * Main tokenizer entry point. Walks the input string, skipping spaces
 * and dispatching to handle_operator or handle_word depending on the
 * current character. On any allocation failure the partial list is
 * freed and NULL is returned so the caller knows something went wrong.
 */
t_token	*tokenize(char *line, t_shell *shell)
{
	t_token	*list;
	t_token	*tok;
	int		i;

	list = NULL;
	i = 0;
	(void)shell;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			tok = handle_operator(line, &i);
		else
			tok = handle_word(line, &i);
		if (!tok)
		{
			free_tokens(list);
			return (NULL);
		}
		add_token_back(&list, tok);
	}
	return (list);
}
