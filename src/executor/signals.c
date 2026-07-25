/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:33:13 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:33:14 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Global variable to store the last received signal number.
*/
volatile sig_atomic_t	g_signal = 0;

/*
** Handles signals in interactive mode (e.g., while waiting for user input).
*/
void	signal_handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
** Configures signal handling for interactive shell mode.
*/
void	setup_signals_interactive(void)
{
	setup_signal_action(SIGINT, signal_handler_interactive, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, 0);
}

/*
** Sets signal handling during command pipeline execution.
*/
void	setup_signals_executing(void)
{
	setup_signal_action(SIGINT, SIG_IGN, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, SA_RESTART);
}

/*
** Restores default signal handling in a child process.
*/
void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
