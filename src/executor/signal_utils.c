/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sets a custom action for a specific signal.
*/
void	setup_signal_action(int signal, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaction(signal, &sa, NULL);
}

/*
** Handles and translates a child process exit status into a shell exit code.
*/
int	handle_signal_exit_status(int status, t_shell *shell)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			shell->exit_status = 130;
		else if (sig == SIGQUIT)
			shell->exit_status = 131;
		else
			shell->exit_status = 128 + sig;
		return (shell->exit_status);
	}
	else if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	shell->exit_status = 1;
	return (1);
}

/*
** Checks if a signal was received and updates the shell's
** exit status accordingly.
*/
int	check_signal_received(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
		return (130);
	}
	else if (g_signal == SIGQUIT)
	{
		shell->exit_status = 131;
		g_signal = 0;
		return (131);
	}
	g_signal = 0;
	return (0);
}

/*
** Prints a descriptive message based on the received signal and process status.
*/
void	print_signal_message(int signal_number, int status)
{
	if (signal_number == SIGQUIT)
	{
		if (WCOREDUMP(status))
			ft_printf("Quit (core dumped)\n");
		else
			ft_printf("Quit\n");
	}
	else if (signal_number == SIGTERM)
	{
		if (WCOREDUMP(status))
			ft_printf("Terminated (core dumped)\n");
		else
			ft_printf("Terminated\n");
	}
	else if (signal_number == SIGKILL)
		ft_printf("Killed\n");
	else if (signal_number == SIGINT)
		ft_printf("\n");
	else if (signal_number == SIGSEGV)
	{
		if (WCOREDUMP(status))
			ft_printf("Segmentation fault (core dumped)\n");
		else
			ft_printf("Segmentation fault\n");
	}
}
