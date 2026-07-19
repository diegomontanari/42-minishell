/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
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
