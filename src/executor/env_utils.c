/* ************************************************************************** */
/*                                                                            */
/*   env_utils.c                                                              */
/*                                                                            */
/*   Utility functions for reading the environment linked list.               */
/*   get_env_value looks up a variable by key.                                */
/*   env_to_array converts the list to the char** format execve needs.        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Searches the env list for a matching key.
 * Returns the value pointer (not a copy) or NULL if not found.
 */
char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strlen(key) == ft_strlen(env->key)
			&& ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/* Counts the number of nodes in the env list. */
static int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/* Joins key and value with '=' to produce a "KEY=VALUE" string. */
static char	*env_join(t_env *node)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(node->key, "=");
	if (!tmp)
		return (NULL);
	if (!node->value)
		return (tmp);
	line = ft_strjoin(tmp, node->value);
	free(tmp);
	return (line);
}

/*
 * Converts the env linked list to a NULL-terminated char** array.
 * Each entry is "KEY=VALUE", heap-allocated.
 * The caller must free the result with free_split().
 */
char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = env_join(env);
		if (!arr[i])
		{
			free_split(arr);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
