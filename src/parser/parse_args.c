/* ************************************************************************** */
/*                                                                            */
/*   parse_args.c                                                             */
/*                                                                            */
/*   Builds the NULL-terminated args array for each command node.            */
/*   Each call appends one string, reallocating the array by one slot.       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Counts the number of strings in a NULL-terminated array.
 * Returns 0 if args is NULL.
 */
static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

/*
 * Appends a copy of value to cmd->args, growing the array by one slot.
 * The array stays NULL-terminated so it is always ready for execve.
 * Returns 0 on success, -1 on allocation failure.
 */
int	add_arg(t_cmd *cmd, char *value)
{
	int		count;
	char	**new_args;
	int		i;

	count = count_args(cmd->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (-1);
	i = -1;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (0);
}
