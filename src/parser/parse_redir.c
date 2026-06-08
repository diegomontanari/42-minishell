/* ************************************************************************** */
/*                                                                            */
/*   parse_redir.c                                                            */
/*                                                                            */
/*   Handles redirection tokens: extracts the type and the filename that    */
/*   follows, creates a t_redir node, and attaches it to the current cmd.   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Returns 1 if the token type represents a redirection, 0 otherwise.
 */
int	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

/*
 * Maps a token type to the corresponding redir type.
 */
static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

/*
 * Allocates a new t_redir node with a heap-copy of file.
 * Returns NULL on malloc failure.
 */
static t_redir	*new_redir(char *file, t_redir_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

/*
 * Appends a redir node to the end of the command's redir list.
 */
static void	add_redir_back(t_redir **list, t_redir *redir)
{
	t_redir	*cur;

	if (!*list)
	{
		*list = redir;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = redir;
}

/*
 * Creates a t_redir from the current token (the operator) and the next
 * token (the filename). Attaches it to cmd and advances *tok past the
 * filename so the main loop skips it.
 * Returns -1 if the filename token is missing (syntax error) or
 * if allocation fails.
 */
int	add_redir(t_cmd *cmd, t_token **tok)
{
	t_redir	*redir;

	if (!(*tok)->next || (*tok)->next->type != TOKEN_WORD)
		return (-1);
	redir = new_redir((*tok)->next->value,
			get_redir_type((*tok)->type));
	if (!redir)
		return (-1);
	add_redir_back(&cmd->redirs, redir);
	*tok = (*tok)->next;
	return (0);
}
