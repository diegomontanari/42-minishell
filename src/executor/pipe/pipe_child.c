/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:32:10 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:32:11 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static void	close_exec_backups(t_shell *shell)
{
	close_pipeline_heredocs(shell->cmds);
	if (shell->stdin_backup >= 0)
	{
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
	if (shell->stdout_backup >= 0)
	{
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
}

/*
** execute_builtin_child
**
** This helper function runs a builtin command inside a child
** process.
*/
static void	execute_builtin_child(t_cmd *curr, t_shell *shell)
{
	int	status;

	if (ft_strcmp(curr->args[0], "exit") == 0 && !curr->args[1])
		shell->exit_status = 0;
	status = handle_builtin(curr->args, shell);
	if (curr->tokens)
	{
		restore_redirection(shell);
		clear_token_list(&curr->tokens);
	}
	full_shell_cleanup(shell);
	exit(status);
}

static void	handle_execve_failure(t_cmd *curr, char *path,
					t_shell *shell, int exec_error)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit_shell(curr, shell, 126);
	}
	ft_putstr_fd("minishell: ", 2);
	errno = exec_error;
	perror(path);
	if (exec_error == ENOENT || exec_error == ENOTDIR)
		exit_shell(curr, shell, 127);
	exit_shell(curr, shell, 126);
}

static void	execute_system_command(t_cmd *curr, t_shell *shell)
{
	char		**envp;
	const char	*cmd;
	int			exec_error;

	cmd = "";
	if (!curr->path)
	{
		if (curr->args && curr->args[0])
			cmd = curr->args[0];
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_shell(curr, shell, 127);
	}
	close_exec_backups(shell);
	envp = build_envp_from_list(shell->env);
	if (!envp)
		exit_shell(curr, shell, 1);
	if (execve(curr->path, curr->args, envp) == -1)
	{
		exec_error = errno;
		free_str_array(envp);
		handle_execve_failure(curr, curr->path, shell, exec_error);
	}
}

/*
** execute_child_process
**
** This function executes a command in the child process.
*/
void	execute_child_process(t_cmd *curr, int prev_fd,
								int *pipe_fd, t_shell *shell)
{
	setup_child_io_and_signals(curr, prev_fd, pipe_fd, shell);
	if (!curr->args || !curr->args[0])
		exit_shell(curr, shell, 0);
	if (curr->type == CMD_BUILTIN)
		execute_builtin_child(curr, shell);
	else
		execute_system_command(curr, shell);
}
