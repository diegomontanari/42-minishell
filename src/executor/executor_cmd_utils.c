/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:32:45 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:32:46 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

/*
** Sets up I/O redirections based on the provided token list.
*/
int	setup_redirection(t_token *tokens, char **args, t_shell *shell)
{
	int	status;

	status = handle_redirection_with_tokens(tokens, shell);
	if (status < 0)
	{
		free_str_array(args);
		shell->exit_status = 1;
		if (status == -2)
			shell->exit_status = 130;
		return (-1);
	}
	return (0);
}

int	check_command_path_access(char *command_path, char *arg0,
				struct stat *path_stat)
{
	if (stat(command_path, path_stat) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg0);
		free(command_path);
		return (127);
	}
	if (S_ISDIR(path_stat->st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command_path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(command_path);
		return (126);
	}
	if (access(command_path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(command_path);
		free(command_path);
		return (126);
	}
	return (0);
}
