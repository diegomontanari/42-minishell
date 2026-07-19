/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles the `pwd` built-in command by printing the current
** working directory to standard output.
** 1. Use `getcwd(NULL, 0)` to dynamically allocate and retrieve
**    the absolute path of the current directory.
** 2. If `getcwd` returns NULL, call `exit_with_error` to print
**    an error message and exit.
** 3. Print the current directory path followed by a newline.
** 4. Free the memory allocated by `getcwd`.
** 5. Return 0 to indicate successful execution.
*/
int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit_with_error("getcwd", NULL, 0, 1);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
