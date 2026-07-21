#include "minishell.h"

/*
** Creates a string in the format "key=value" from a `t_env` node.
*/
static char	*create_key_value_string(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	if (env->value)
	{
		result = ft_strjoin(tmp, env->value);
		free(tmp);
		if (!result)
			return (NULL);
	}
	else
		result = tmp;
	return (result);
}

/*
** Builds an environment array (`envp`) from a linked list of `t_env` nodes.
*/
char	**build_envp_from_list(t_env *env)
{
	size_t	env_count;
	char	**environment_array;
	size_t	i;

	env_count = count_env_nodes(env);
	environment_array = ft_calloc(env_count + 1, sizeof(*environment_array));
	if (!environment_array)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->exported && env->value)
		{
			environment_array[i] = create_key_value_string(env);
			if (!environment_array[i])
				return (free_str_array(environment_array), NULL);
			i++;
		}
		env = env->next;
	}
	environment_array[i] = NULL;
	return (environment_array);
}
