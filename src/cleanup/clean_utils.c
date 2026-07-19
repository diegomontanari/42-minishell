#include "minishell.h"

/*
** free_partial_paths (was free_partial_paths)
** Frees a partially allocated array of strings after an error.
*/
void	free_partial_paths(char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(paths[i++]);
	free(paths);
}

/*
** free_str_array (was free_str_array)
** Frees a NULL-terminated array of strings.
*/
void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

/*
** free_multiple_ptrs (was free_parts)
** Frees up to three dynamically allocated strings.
*/
void	free_multiple_ptrs(char *a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
}

/*
** free_paths
** Frees a NULL-terminated array of path strings.
*/
void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

/*
** exit_shell (was exit_shell)
** This function frees allocated resources and terminates the program.
*/
void	exit_shell(t_cmd *curr, t_shell *shell, int exit_code)
{
	if (curr && curr->tokens)
	{
		restore_redirection(shell);
		clear_token_list(&curr->tokens);
	}
	full_shell_cleanup(shell);
	exit(exit_code);
}
