/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** identify_redir_type
**
** This static helper determines the type of a redirection operator.
** - If the operator is "<<", return TK_HEREDOC and set *len to 2.
** - If the operator is ">>", return TK_APPEND and set *len to 2.
** - If the operator is ">", return TK_OUT and set *len to 1.
** - Otherwise (only "<"), return TK_IN and set *len to 1.
*/
static int	identify_redir_type(char first, char second, int *len)
{
	if (first == '<' && second == '<')
		return (*len = 2, TK_HEREDOC);
	else if (first == '>' && second == '>')
		return (*len = 2, TK_APPEND);
	else if (first == '>')
		return (*len = 1, TK_OUT);
	else
		return (*len = 1, TK_IN);
}

/*
** add_redir_token
**
** This function processes a redirection operator from the input.
** - Identifies the redirection type (<, >, <<, >>) and advances
**   the input position.
** - Creates the appropriate string representation based on type.
** - Creates a token with the string and type, adds it to the list.
** - Frees the temporary string after use.
*/
void	add_redir_token(t_token_ctx *ctx)
{
	int		type;
	int		len;
	char	*str;

	type = identify_redir_type(ctx->input[*ctx->i],
			ctx->input[*ctx->i + 1], &len);
	*ctx->i += len;
	if (type == TK_HEREDOC)
		str = ft_strdup("<<");
	else if (type == TK_APPEND)
		str = ft_strdup(">>");
	else if (type == TK_OUT)
		str = ft_strdup(">");
	else
		str = ft_strdup("<");
	add_token_to_list(ctx->tokens, new_token(str, type, 0));
	free(str);
}
