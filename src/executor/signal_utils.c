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

static void	print_core_message(char *plain, char *core, int status)
{
	if (WCOREDUMP(status))
		ft_putstr_fd(core, STDOUT_FILENO);
	else
		ft_putstr_fd(plain, STDOUT_FILENO);
}

/*
** Prints a descriptive message based on the received signal and process status.
*/
void	print_signal_message(int signal_number, int status)
{
	if (signal_number == SIGQUIT)
		print_core_message("Quit\n", "Quit (core dumped)\n", status);
	else if (signal_number == SIGTERM)
		print_core_message("Terminated\n",
			"Terminated (core dumped)\n", status);
	else if (signal_number == SIGKILL)
		ft_printf("Killed\n");
	else if (signal_number == SIGINT)
		ft_printf("\n");
	else if (signal_number == SIGSEGV)
		print_core_message("Segmentation fault\n",
			"Segmentation fault (core dumped)\n", status);
}
