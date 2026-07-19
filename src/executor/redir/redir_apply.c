/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** restore_input_redirection
**
** This function restores the original STDIN after an input
** redirection has been applied.
*/
void	restore_input_redirection(t_shell *shell)
{
	if (shell->stdin_backup >= 0)
	{
		if (dup2(shell->stdin_backup, 0) == -1)
			perror("dup2");
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
}

/*
** update_input_fd
**
** This function updates the current input file descriptor.
*/
void	update_input_fd(int *input_fd, int new_input_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	*input_fd = new_input_fd;
}

/*
** setup_output_redirection
**
** This function applies an output redirection.
*/
int	setup_output_redirection(int file_fd, t_shell *shell)
{
	int	saved_fd;

	if (file_fd == -1)
		return (0);
	saved_fd = dup(1);
	if (saved_fd == -1)
	{
		perror("minishell");
		close(file_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	if (dup2(file_fd, 1) == -1)
	{
		perror("minishell");
		close(file_fd);
		close(saved_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	close(file_fd);
	shell->stdout_backup = saved_fd;
	return (0);
}
