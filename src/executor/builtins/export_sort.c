/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:31:55 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:31:56 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_min_index(t_env **arr, int size, int start)
{
	int	min_idx;
	int	i;

	min_idx = start;
	i = start + 1;
	while (i < size)
	{
		if (ft_strcmp(arr[i]->key, arr[min_idx]->key) < 0)
			min_idx = i;
		i++;
	}
	return (min_idx);
}

static void	swap_env(t_env **arr, int i, int j)
{
	t_env	*temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/*
** Sorts an array of environment variable pointers by key
** using the selection sort algorithm.
*/
void	selection_sort_env(t_env **arr, int size)
{
	int	i;
	int	min_idx;

	i = 0;
	while (i < size - 1)
	{
		min_idx = find_min_index(arr, size, i);
		if (min_idx != i)
			swap_env(arr, i, min_idx);
		i++;
	}
}

t_env	**env_list_to_array(t_env *env, int size)
{
	t_env	**array;
	int		i;

	array = ft_calloc(size, sizeof(t_env *));
	if (!array)
		return (NULL);
	i = 0;
	while (env && i < size)
	{
		array[i++] = env;
		env = env->next;
	}
	return (array);
}
