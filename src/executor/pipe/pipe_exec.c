/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/*
** setup_next_pipe
**
** This helper function determines the read end of the next pipe
** for a command in a pipeline.
*/
static int	setup_next_pipe(t_cmd *curr, int pipe_fd[2])
{
	if (curr->next)
	{
		if (has_output_redirection(curr->tokens))
			return (-1);
		else
			return (pipe_fd[0]);
	}
	return (-1);
}

/*
** execute_commands_loop
**
** This function executes a list of commands connected by pipes.
*/
static int	execute_commands_loop(t_cmd *cmds, t_shell *shell, pid_t *last_pid)
{
	int		fds[3];
	t_cmd	*curr;
	int		error_occurred;

	fds[0] = -1;
	curr = cmds;
	error_occurred = 0;
	while (curr && !error_occurred)
	{
		if (execute_single_command(curr, fds, shell, last_pid) != 0)
		{
			error_occurred = 1;
			break ;
		}
		fds[0] = setup_next_pipe(curr, fds + 1);
		curr = curr->next;
	}
	if (error_occurred && fds[0] != -1)
		close(fds[0]);
	return (error_occurred);
}

static int	wait_for_children(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		last_status;

	last_status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = handle_signal_exit_status(status, shell);
		else
			handle_signal_exit_status(status, shell);
		pid = waitpid(-1, &status, 0);
	}
	shell->exit_status = last_status;
	return (last_status);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		error_occurred;
	pid_t	last_pid;

	last_pid = -1;
	setup_signals_executing();
	error_occurred = execute_commands_loop(cmds, shell, &last_pid);
	if (error_occurred)
	{
		setup_signals_interactive();
		return (1);
	}
	wait_for_children(last_pid, shell);
	setup_signals_interactive();
	return (shell->exit_status);
}

/*
** handle_pipeline_execution
**
** This function manages the execution of a full pipeline.
*/
int	handle_pipeline_execution(t_token *tokens, t_shell *shell)
{
	int	status;

	shell->cmds = parser_build_cmd_list(tokens, shell);
	if (!shell->cmds)
		return (-1);
	status = execute_pipeline(shell->cmds, shell);
	shell->exit_status = status;
	return (status);
}
