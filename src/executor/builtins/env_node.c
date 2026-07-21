#include "minishell.h"

/*
** Appends a new environment node to the end of the list.
*/
int	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!*env_list)
	{
		*env_list = new_node;
		return (1);
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (1);
}

/*
** Updates the value and export status of an environment node.
*/
int	update_env_node(t_env *node, char *new_value, int exported_flag)
{
	if (!node)
		return (0);
	free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
	if (new_value && !node->value)
		return (0);
	node->exported = exported_flag;
	return (1);
}

/*
** Searches for an environment variable node by key.
*/
t_env	*find_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
