#include "minishell.h"

/*
** setup_command_execution
**
** This function prepares a command for execution by creating
** pipes (if needed) and forking a child process.
*/
int	setup_command_execution(t_cmd *curr, int *fds, pid_t *pid)
{
	fds[1] = -1;
	fds[2] = -1;
	if (curr->next && pipe(fds + 1) == -1)
		return (print_error("pipe"));
	*pid = fork();
	if (*pid == -1)
	{
		if (fds[1] != -1)
			close(fds[1]);
		if (fds[2] != -1)
			close(fds[2]);
		return (print_error("fork"));
	}
	return (0);
}

/*
** execute_single_command
**
** This function executes one command in a pipeline.
*/
int	execute_single_command(t_cmd *curr, int *fds,
		t_shell *shell, pid_t *last_pid)
{
	pid_t	pid;

	if (setup_command_execution(curr, fds, &pid) != 0)
		return (1);
	*last_pid = pid;
	if (pid == 0)
		execute_child_process(curr, fds[0], fds + 1, shell);
	if (fds[0] != -1)
		close(fds[0]);
	if (curr->next)
		close(fds[2]);
	return (0);
}
