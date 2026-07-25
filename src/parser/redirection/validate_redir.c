/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:33:31 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:33:32 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	validate_redirection_syntax(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TK_IN || tokens->type == TK_HEREDOC
			|| tokens->type == TK_OUT || tokens->type == TK_APPEND)
		{
			if (valid_syntax_token(tokens) == -1)
				return (-1);
		}
		tokens = tokens->next;
	}
	return (0);
}
