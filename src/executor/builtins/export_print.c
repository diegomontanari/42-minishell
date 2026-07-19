#include "minishell.h"

/*
** This function prints exported environment variables from
** an array recursively.
*/
void	print_exported_recursive(t_env **arr, int size, int i)
{
	t_env	*node;

	node = arr[i];
	if (i >= size)
		return ;
	if (node->exported)
	{
		ft_printf("declare -x %s", node->key);
		if (node->value)
			ft_printf("=\"%s\"", node->value);
		ft_printf("\n");
	}
	print_exported_recursive(arr, size, i + 1);
}

/*
** This function prints the environment variables in sorted order.
*/
void	print_export_sorted(t_env *env_list)
{
	int		size;
	t_env	**arr;

	size = env_list_size(env_list);
	arr = env_list_to_array(env_list, size);
	if (size == 0)
		return ;
	selection_sort_env(arr, size);
	print_exported_recursive(arr, size, 0);
	free(arr);
}
