/* ************************************************************************** */
/*                                                                            */
/*   builtin_env.c                                                            */
/*                                                                            */
/*   Prints all environment variables in KEY=VALUE format.                    */
/*   Variables exported without a value are skipped (bash behaviour).         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (0);
}
