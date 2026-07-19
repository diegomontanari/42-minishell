/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_setup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles the case when no valid command tokens are found.
*/
int	handle_null_tokens(t_shell *shell)
{
	shell->exit_status = 0;
	return (0);
}

/*
** Prepares the command arguments array excluding redirection tokens.
*/
char	**prepare_cmd_args(t_token *tokens, t_shell *shell)
{
	char	**args;

	(void)shell;
	args = args_extract_from_tokens(tokens);
	if (!args)
	{
		return (NULL);
	}
	return (args);
}
