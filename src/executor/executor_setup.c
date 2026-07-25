/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:32:52 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:32:53 by pscarcin         ###   ########.fr       */
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
