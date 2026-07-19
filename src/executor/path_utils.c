/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts the number of path segments in a PATH string.
*/
int	count_path_segments(char *path_env)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
			count++;
		i++;
	}
	return (count);
}

/*
** Allocates memory for an array of path strings.
*/
char	**allocate_paths_array(int count)
{
	char	**paths;

	paths = ft_calloc(count + 1, sizeof(char *));
	return (paths);
}

/*
** Extracts a substring representing a single PATH segment.
*/
char	*extract_path_segment(char *path_env, int start, int len)
{
	char	*segment;

	segment = ft_calloc(len + 1, sizeof(char));
	if (!segment)
		return (NULL);
	ft_strncpy(segment, &path_env[start], len);
	return (segment);
}
