/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles the `exit` command when an exit code argument is provided.
*/
static void	handle_exit_with_code(t_shell *shell, char **args, char *exit_code)
{
	if (!is_numeric(exit_code) || check_atol_conversion(exit_code))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd(exit_code, STDERR_FILENO);
		ft_putendl_fd("numeric argument required", STDERR_FILENO);
		shell->exit_status = 255;
		free_str_array(args);
		full_shell_cleanup(shell);
		exit(2);
	}
	else
		shell->exit_status = ft_atoi(exit_code);
}

/*
** Handles the `exit` built-in command and its arguments.
*/
int	handle_exit(t_shell *shell, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		shell->exit_status = 0;
		return (0);
	}
	else if (argc == 2)
	{
		handle_exit_with_code(shell, args, args[1]);
		return (0);
	}
	else
	{
		ft_putendl_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
}
