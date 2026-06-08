/* ************************************************************************** */
/*                                                                            */
/*   builtin_export_utils.c                                                   */
/*                                                                            */
/*   Helper functions for builtin_export: identifier validation,              */
/*   error printing, and environment node lookup/creation.                    */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Returns 1 if name is a valid env variable identifier. */
int	valid_identifier(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/* Finds existing var or appends a new node. Returns the target node. */
t_env	*find_or_create(char *key, t_shell *shell)
{
	t_env	*env;
	t_env	*last;

	env = shell->env;
	last = NULL;
	while (env)
	{
		if (ft_strlen(key) == ft_strlen(env->key)
			&& ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			return (env);
		last = env;
		env = env->next;
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = NULL;
	env->next = NULL;
	if (last)
		last->next = env;
	return (env);
}
