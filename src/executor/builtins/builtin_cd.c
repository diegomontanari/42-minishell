/* ************************************************************************** */
/*                                                                            */
/*   builtin_cd.c                                                             */
/*                                                                            */
/*   Changes the current working directory.                                   */
/*   With no argument, goes to $HOME.                                         */
/*   Updates OLDPWD to the previous directory and PWD to the new one.         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Updates or creates an env variable with the given key and value. */
static void	set_env_value(char *key, char *value, t_env *env)
{
	while (env)
	{
		if (ft_strlen(key) == ft_strlen(env->key)
			&& ft_strncmp(key, env->key, ft_strlen(key)) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

/* Resolves the target directory: argument or $HOME. */
static char	*get_target(t_cmd *cmd, t_shell *shell)
{
	char	*home;

	if (cmd->args[1])
		return (cmd->args[1]);
	home = get_env_value("HOME", shell->env);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (home);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*target;
	char	old_pwd[PATH_MAX];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	target = get_target(cmd, shell);
	if (!target)
		return (1);
	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0';
	if (chdir(target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(target);
		return (1);
	}
	set_env_value("OLDPWD", old_pwd, shell->env);
	set_env_value("PWD", target, shell->env);
	return (0);
}
