/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:32:20 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:32:21 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check_for_pipes
**
** This function scans the token list to see if there are
** any pipe operators ("|").
*/
int	check_for_pipes(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

/*
** create_new_cmd
**
** This function allocates and initializes a new command node.
*/
t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->path = NULL;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->next = NULL;
	new_cmd->type = 0;
	return (new_cmd);
}

/*
** check_syntax_pipes
**
** This function validates the correct syntax of pipes ("|").
*/
int	check_syntax_pipes(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;

	if (!tokens)
		return (0);
	prev = NULL;
	curr = tokens;
	if (curr->type == TK_PIPE)
		return (print_pipe_error());
	while (curr)
	{
		if (curr->type == TK_PIPE && prev && prev->type == TK_PIPE)
			return (print_pipe_error());
		prev = curr;
		curr = curr->next;
	}
	if (prev && prev->type == TK_PIPE)
		return (print_pipe_error());
	return (0);
}
