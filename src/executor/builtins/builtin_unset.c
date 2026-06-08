/* ************************************************************************** */
/*                                                                            */
/*   builtin_unset.c                                                          */
/*                                                                            */
/*   Removes variables from the environment list by key.                      */
/*   Invalid identifiers are silently ignored (bash behaviour).               */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Removes one env node matching key, relinking the list around it. */
static void	unset_one(char *key, t_shell *shell)
{
	t_env	*env;
	t_env	*prev;

	if (!valid_identifier(key))
		return ;
	env = shell->env;
	prev = NULL;
	while (env)
	{
		if (ft_strlen(key) == ft_strlen(env->key)
			&& ft_strncmp(key, env->key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				shell->env = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		unset_one(cmd->args[i], shell);
	return (0);
}
