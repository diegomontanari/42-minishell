/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Retrieves the value of an environment variable by key.
*/
char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
** Updates the value of an existing environment variable
** if it is found in the environment list.
*/
int	update_env_value_if_exists(t_env *envp, const char *key, const char *value)
{
	t_env	*node;

	node = find_env_node(envp, (char *)key);
	if (!node)
		return (1);
	if (update_env_node(node, (char *)value, node->exported))
		return (0);
	return (1);
}

/*
** Appends a new environment variable if it does not already exist.
*/
int	append_env_value_if_missing(t_env **envp, const char *key,
									const char *value)
{
	t_env	*exists;
	t_env	*node;

	exists = find_env_node(*envp, (char *)key);
	if (exists)
		return (0);
	node = create_env_node((char *)key, (char *)value, 1);
	if (!node)
		return (1);
	if (add_env_node(envp, node))
		return (0);
	return (1);
}

/*
** Sets an environment variable to a specified value.
*/
int	set_env_value(t_env **envp, const char *key, const char *value)
{
	if (update_env_value_if_exists(*envp, key, value) == 0)
		return (0);
	return (append_env_value_if_missing(envp, key, value));
}
