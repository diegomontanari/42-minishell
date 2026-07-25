/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:32:17 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:32:18 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** setup_child_input
*/
static void	setup_child_input(t_cmd *curr, int prev_fd)
{
	int	has_input_redir;

	if (prev_fd == -1)
		return ;
	has_input_redir = has_input_redirection(curr->tokens);
	if (!has_input_redir)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	close(prev_fd);
}

static void	setup_child_output(t_cmd *curr, int *pipe_fd)
{
	int	has_output_redir;

	if (!curr->next || !pipe_fd)
		return ;
	has_output_redir = has_output_redirection(curr->tokens);
	close(pipe_fd[0]);
	if (!has_output_redir)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	close(pipe_fd[1]);
}

static void	setup_child_pipes(t_cmd *curr, int prev_fd, int *pipe_fd)
{
	setup_child_input(curr, prev_fd);
	setup_child_output(curr, pipe_fd);
}

/*
** setup_child_redir_and_signals
*/
static void	setup_child_redir_and_signals(t_cmd *curr, t_shell *shell)
{
	int	status;

	if (curr->tokens)
	{
		status = handle_redirection_with_tokens(curr->tokens, shell);
		if (status < 0)
		{
			if (status == -2)
				shell->exit_status = 130;
			else
				shell->exit_status = 1;
			full_shell_cleanup(shell);
			exit(shell->exit_status);
		}
	}
	setup_signals_child();
}

/*
 * setup_child_io_and_signals:
 * Entry point combining pipes setup and
 * redirections/signals configuration.
 */
void	setup_child_io_and_signals(t_cmd *curr,
					int prev_fd, int *pipe_fd, t_shell *shell)
{
	setup_sigpipe_handling();
	setup_child_pipes(curr, prev_fd, pipe_fd);
	setup_child_redir_and_signals(curr, shell);
}
