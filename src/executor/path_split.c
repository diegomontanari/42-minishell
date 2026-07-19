#include "minishell.h"

/* state[0] = i, state[1] = j */
static int	process_path_segment(char *path_env, char **paths,
								int start, int state[2])
{
	int	len;
	int	is_delim;
	int	is_end;

	is_delim = (path_env[state[0]] == ':');
	is_end = (path_env[state[0] + 1] == '\0');
	if (is_delim || is_end)
	{
		if (is_delim)
			len = state[0] - start;
		else
			len = state[0] - start + 1;
		paths[state[1]] = extract_path_segment(path_env, start, len);
		if (!paths[state[1]])
		{
			free_partial_paths(paths, state[1]);
			return (-1);
		}
		state[1] += 1;
		return (1);
	}
	return (0);
}

static int	iterate_path_string(char *path_env, char **paths)
{
	int	state[2];
	int	start;
	int	result;

	state[0] = 0;
	state[1] = 0;
	start = 0;
	while (path_env[state[0]])
	{
		result = process_path_segment(path_env, paths, start, state);
		if (result == -1)
			return (-1);
		if (result == 1)
			start = state[0] + 1;
		state[0]++;
	}
	paths[state[1]] = NULL;
	return (0);
}

static int	parse_and_fill_paths(char *path_env, char **paths)
{
	if (!path_env || !path_env[0])
	{
		paths[0] = NULL;
		return (0);
	}
	return (iterate_path_string(path_env, paths));
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
	if (parse_and_fill_paths(path_env, paths) == -1)
		return (NULL);
	return (paths);
}
