/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:31:50 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:31:51 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static int	exit_code_value(char *str)
{
	int	i;
	int	negative;
	int	status;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	negative = (str[i] == '-');
	if (str[i] == '+' || str[i] == '-')
		i++;
	status = 0;
	while (str[i] >= '0' && str[i] <= '9')
		status = (status * 10 + str[i++] - '0') % 256;
	if (negative && status != 0)
		status = 256 - status;
	return (status);
}

/*
** Handles the `exit` built-in command and its arguments.
*/
int	handle_exit(t_shell *shell, char **args)
{
	if (!args[1])
		return (shell->exit_status);
	if (!is_numeric(args[1]) || check_atol_conversion(args[1]))
	{
		print_numeric_error(args[1]);
		shell->exit_status = 2;
		return (2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = exit_code_value(args[1]);
	return (shell->exit_status);
}
