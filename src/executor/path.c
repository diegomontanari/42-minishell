#include "minishell.h"

static char	*build_full_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	if (!dir[0])
		return (ft_strdup(command));
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	return (free(temp), full_path);
}

static char	*search_command_in_paths(char **paths, char *command)
{
	char		*full_path;
	char		*denied_path;
	int			i;
	struct stat	path_stat;

	i = 0;
	denied_path = NULL;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], command);
		if (!full_path)
			return (free(denied_path), NULL);
		if (access(full_path, X_OK) == 0
			&& stat(full_path, &path_stat) == 0
			&& !S_ISDIR(path_stat.st_mode))
			return (free(denied_path), full_path);
		if (!denied_path && access(full_path, F_OK) == 0)
			denied_path = full_path;
		else
			free(full_path);
		i++;
	}
	return (denied_path);
}

static char	*search_in_path_dirs(char *command, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*result;

	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = split_path_env(path_env);
	if (!paths)
		return (NULL);
	result = search_command_in_paths(paths, command);
	return (free_paths(paths), result);
}

/*
** Determines the full path of a command to execute.
*/
char	*find_command_path(char *command, t_shell *shell)
{
	if (!command || !*command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	return (search_in_path_dirs(command, shell));
}
