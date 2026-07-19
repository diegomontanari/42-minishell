#include "minishell.h"

/*
** create_pipe_and_setup
**
** This function creates a pipe and sets up signals for execution.
*/
int	create_pipe_and_setup(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (1);
	setup_signals_executing();
	return (0);
}

/*
** handle_pipe
**
** This function handles execution of two commands connected
** by a pipe.
*/
int	handle_pipe(t_cmd *cmd1, t_cmd *cmd2, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (!cmd1 || !cmd2 || !shell)
		return (print_error("Error: pipe"));
	if (create_pipe_and_setup(pipe_fd) != 0)
		return (1);
	pid1 = fork_first_child(cmd1, shell, pipe_fd);
	if (pid1 == -1)
		return (-1);
	pid2 = fork_second_child(cmd2, shell, pipe_fd, pid1);
	if (pid2 == -1)
		return (1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	handle_signal_exit_status(status2, shell);
	setup_signals_interactive();
	return (shell->exit_status);
}
