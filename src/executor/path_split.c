/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:33:01 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:33:02 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	iterate_path_string(char *path_env, char **paths)
{
	int	state[2];
	int	start;
	int	len;

	state[0] = 0;
	state[1] = 0;
	start = 0;
	while (1)
	{
		if (path_env[state[0]] == ':' || path_env[state[0]] == '\0')
		{
			len = state[0] - start;
			paths[state[1]] = extract_path_segment(path_env, start, len);
			if (!paths[state[1]])
				return (free_partial_paths(paths, state[1]), -1);
			state[1]++;
			if (path_env[state[0]] == '\0')
				break ;
			start = state[0] + 1;
		}
		state[0]++;
	}
	paths[state[1]] = NULL;
	return (0);
}

/*
** Splits the PATH environment variable into an array of
** directory paths.
*/
char	**split_path_env(char *path_env)
{
	char	**paths;
	int		count;

	if (!path_env)
		return (NULL);
	count = count_path_segments(path_env);
	paths = allocate_paths_array(count);
	if (!paths)
		return (NULL);
	if (iterate_path_string(path_env, paths) == -1)
		return (NULL);
	return (paths);
}
