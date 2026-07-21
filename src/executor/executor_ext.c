#include "minishell.h"

/*
** execute_exit
*/
int	execute_exit(char **args, t_shell *shell)
{
	int	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	status = handle_exit(shell, args);
	if (status == 1 && args[1] && args[2])
		return (status);
	restore_redirection(shell);
	free_str_array(args);
	full_shell_cleanup(shell);
	exit(status);
}

/*
** handle_other_builtins
*/
int	handle_other_builtins(char **args, t_shell *shell)
{
	return (handle_builtin(args, shell));
}

static void	execute_child_process_from_args(char *cmd_path, char **args,
				t_shell *shell)
{
	t_cmd	temp;

	temp.path = cmd_path;
	temp.args = args;
	temp.next = NULL;
	temp.type = CMD_EXTERNAL;
	temp.tokens = NULL;
	temp.fd_in = STDIN_FILENO;
	temp.fd_out = STDOUT_FILENO;
	execute_child_process(&temp, -1, NULL, shell);
}

static void	handle_parent_process(pid_t pid, t_shell *shell)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		if (g_signal == SIGINT)
			shell->exit_status = 130;
		else
		{
			perror("waitpid");
			shell->exit_status = 1;
		}
	}
	else
	{
		if (WIFSIGNALED(status))
			print_signal_message(WTERMSIG(status), status);
		handle_signal_exit_status(status, shell);
	}
	setup_signals_interactive();
	reset_loop_state(shell);
}

int	execute_external_command(char *cmd_path, char **args, t_shell *shell)
{
	pid_t	pid;

	setup_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		setup_signals_interactive();
		exit_with_error("fork", shell, 1, 1);
	}
	else if (pid == 0)
		execute_child_process_from_args(cmd_path, args, shell);
	else
		handle_parent_process(pid, shell);
	return (shell->exit_status);
}
