/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

/*
** execute_builtin_child
**
** This helper function runs a builtin command inside a child
** process.
*/
static void	execute_builtin_child(t_cmd *curr, t_shell *shell)
{
	int	status;

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
				struct s_shell *shell)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit_shell(curr, shell, 126);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit_shell(curr, shell, 126);
	}
	ft_putstr_fd("minishell: ", 2);
	perror(path);
	exit_shell(curr, shell, 1);
}

static void	execute_system_command(t_cmd *curr, t_shell *shell)
{
	char		**envp;
	const char	*cmd;

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
	envp = build_envp_from_list(shell->env);
	if (!envp)
		exit_shell(curr, shell, 1);
	if (execve(curr->path, curr->args, envp) == -1)
	{
		free_str_array(envp);
		handle_execve_failure(curr, curr->path, shell);
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
	if (curr->type == CMD_BUILTIN)
		execute_builtin_child(curr, shell);
	else
		execute_system_command(curr, shell);
}
