/* ************************************************************************** */
/*                                                                            */
/*   find_path.c                                                              */
/*                                                                            */
/*   Resolves a command name to its full filesystem path.                     */
/*   If the name already contains a slash it is used as-is.                   */
/*   Otherwise each directory listed in $PATH is tried until an               */
/*   executable is found.                                                     */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/* Joins a directory and command name with a '/' separator. */
static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

/* Tries each $PATH directory and returns the first executable match. */
static char	*search_in_path(char *cmd, char *path_value)
{
	char	**dirs;
	char	*full;
	int		i;

	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (NULL);
	i = -1;
	while (dirs[++i])
	{
		full = join_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0)
		{
			free_split(dirs);
			return (full);
		}
		free(full);
	}
	free_split(dirs);
	return (NULL);
}

/*
 * If cmd contains '/' it is a direct path: return a dup if executable.
 * Otherwise search $PATH directories.
 * Returns heap-allocated path or NULL if not found.
 */
char	*find_path(char *cmd, t_env *env)
{
	char	*path_value;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_value = get_env_value("PATH", env);
	if (!path_value)
		return (NULL);
	return (search_in_path(cmd, path_value));
}
