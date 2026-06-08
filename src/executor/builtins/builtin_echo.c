/* ************************************************************************** */
/*                                                                            */
/*   builtin_echo.c                                                           */
/*                                                                            */
/*   Prints arguments to stdout separated by spaces.                          */
/*   The -n flag suppresses the trailing newline.                             */
/*   Multiple -n flags are allowed (echo -n -n -n hello).                     */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Returns 1 if the argument is a valid -n flag.
 * Valid means: starts with '-' followed by one or more 'n' chars only.
 * Examples: "-n" yes, "-nnn" yes, "-na" no, "-" no.
 */
static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
