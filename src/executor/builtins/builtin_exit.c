/* ************************************************************************** */
/*                                                                            */
/*   builtin_exit.c                                                           */
/*                                                                            */
/*   Exits the shell with an optional numeric status code.                    */
/*   "exit" alone uses the last $? value. Non-numeric argument is an error.   */
/*   Too many arguments prints an error but does NOT exit.                    */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Returns 1 if str is a valid integer (optional leading +/-). */
static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Prints "exit" to stderr (bash prints it even in non-interactive mode). */
static void	print_exit(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	long long	code;

	print_exit();
	if (!cmd->args[1])
		exit(shell->exit_status);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	code = ft_atoi(cmd->args[1]);
	exit((unsigned char)code);
}
