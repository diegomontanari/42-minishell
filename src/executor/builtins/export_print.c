#include "minishell.h"

static int	needs_export_escape(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

static void	print_export_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (needs_export_escape(value[i]))
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(value[i], STDOUT_FILENO);
		i++;
	}
}

/*
** This function prints exported environment variables from
** an array recursively.
*/
void	print_exported_recursive(t_env **arr, int size, int i)
{
	t_env	*node;

	if (i >= size)
		return ;
	node = arr[i];
	if (node->exported)
	{
		ft_printf("declare -x %s", node->key);
		if (node->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			print_export_value(node->value);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
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
	if (!arr || size == 0)
	{
		free(arr);
		return ;
	}
	selection_sort_env(arr, size);
	print_exported_recursive(arr, size, 0);
	free(arr);
}
