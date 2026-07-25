/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:32:24 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:32:25 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_command_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_token	*token;
	int		fd;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == TK_HEREDOC)
		{
			fd = create_heredoc_pipe(token->next->value,
					token->next->is_quoted, shell);
			if (fd < 0)
				return (fd);
			token->heredoc_fd = fd;
		}
		token = token->next;
	}
	return (0);
}

int	prepare_pipeline_heredocs(t_cmd *cmds, t_shell *shell)
{
	int	status;

	while (cmds)
	{
		status = prepare_command_heredocs(cmds, shell);
		if (status < 0)
			return (status);
		cmds = cmds->next;
	}
	return (0);
}

void	close_pipeline_heredocs(t_cmd *cmds)
{
	t_token	*token;

	while (cmds)
	{
		token = cmds->tokens;
		while (token)
		{
			if (token->heredoc_fd >= 0)
			{
				close(token->heredoc_fd);
				token->heredoc_fd = -1;
			}
			token = token->next;
		}
		cmds = cmds->next;
	}
}
