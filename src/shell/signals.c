/* ************************************************************************** */
/*                                                                            */
/*   signals.c                                                                */
/*                                                                            */
/*   Signal handling for the three shell contexts:                           */
/*   interactive : waiting for input at the prompt.                          */
/*   executing   : a foreground command is running.                          */
/*   child       : inside a forked child process.                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

/*
 * Handler for SIGINT (ctrl-C) in interactive mode.
 * Writes a newline so the next prompt appears on a clean line,
 * then stores the signal number in g_signal so the main loop
 * can set exit_status to 130 (128 + SIGINT) after readline returns.
 * rl_replace_line and rl_on_new_line reset readline's internal state
 * so the prompt is redrawn correctly.
 */
static void	handle_sigint_interactive(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
 * Handler for SIGINT (ctrl-C) while a foreground command is running.
 * Only stores the signal in g_signal — the parent process reads it
 * after waitpid returns and sets exit_status to 130.
 * No output here: the terminal already printed "^C".
 */
static void	handle_sigint_executing(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
}

/*
 * Sets up signal handlers for interactive mode: waiting at the prompt.
 * SIGINT  (ctrl-C) : redraws the prompt on a new line.
 * SIGQUIT (ctrl-\) : ignored — bash does the same at the prompt.
 */
void	signals_interactive(void)
{
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Sets up signal handlers while a foreground command is running.
 * SIGINT  (ctrl-C) : stored in g_signal, parent reads it after waitpid.
 * SIGQUIT (ctrl-\) : ignored in the parent — the child handles it.
 */
void	signals_executing(void)
{
	signal(SIGINT, handle_sigint_executing);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Resets signal handlers to defaults inside a child process, before
 * execve. The child must respond normally to SIGINT and SIGQUIT so
 * the user can interrupt or quit the running program as expected.
 */
void	signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
