#include "minishell.h"

/*
** Allocates and initializes a new environment variable node.
*/
t_env	*create_env_node(char *key, char *value, int exported)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), NULL);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), free(new_node), NULL);
	}
	else
		new_node->value = NULL;
	new_node->exported = exported;
	new_node->next = NULL;
	return (new_node);
}

/*
** Converts a single environment string into a `t_env`
** linked list node.
*/
static t_env	*process_env_entry(char *env_entry)
{
	t_env	*new;
	char	*key;
	char	*value;

	key = extract_key(env_entry);
	value = extract_value(env_entry);
	if (!key)
		return (NULL);
	new = create_env_node(key, value, 1);
	free(key);
	if (value)
		free(value);
	return (new);
}

/*
** Creates a linked list of environment variables from
** an array of strings.
*/
t_env	*copy_env_entries(char **env_entries)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;

	head = NULL;
	tail = NULL;
	while (*env_entries)
	{
		new = process_env_entry(*env_entries);
		if (!new)
			return (clear_env_str(head), NULL);
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		env_entries++;
	}
	return (head);
}

/*
** Counts the total number of environment variable nodes
** in the linked list.
*/
size_t	count_env_nodes(t_env *env)
{
	size_t	env_count;

	env_count = 0;
	while (env)
	{
		env_count++;
		env = env->next;
	}
	return (env_count);
}

/*
** Counts the number of nodes in the environment list.
*/
int	env_list_size(t_env *env)
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
