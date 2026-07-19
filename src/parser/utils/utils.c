/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** count_valid_args
**
** This function counts the number of valid arguments in a
** token list.
** - Iterate through each token in the list.
** - If the token type is TK_WORD:
**     * Check if it is not the target of an input redirection
**       using is_redir_target().
**     * If not a redirection target, increase the count.
** - Return the total number of valid argument tokens found.
*/
int	count_valid_args(t_token *head)
{
	t_token		*curr;
	int			count;

	count = 0;
	curr = head;
	while (curr)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_redir_target(head, curr))
			{
				if (curr->is_quoted || (curr->value && curr->value[0] != '\0'))
					count++;
			}
		}
		curr = curr->next;
	}
	return (count);
}
