/* ************************************************************************** */
/*                                                                            */
/*   pipeline.c                                                               */
/*                                                                            */
/*   Walks the command list and forks one child per segment.                  */
/*   Adjacent children are connected through pipes: the write end of one      */
/*   pipe feeds the read end of the next child's stdin.                       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Waits for all children and saves the last one's exit status in $?. */
static void	wait_children(int last_pid, t_shell *shell)
{
	int	status;
	int	pid;

	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
	}
}

/*
 * Forks one child for cmd, wiring prev_fd as stdin and pfd[1] as stdout.
 * Returns the child's pid so the parent can track the last one.
 */
static int	fork_cmd(t_cmd *cmd, int prev_fd, int pfd[2],
		t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
		exec_child(cmd, prev_fd, pfd, shell);
	return (pid);
}

/*
 * Iterates through the command list, creating pipes between adjacent
 * commands and forking a child for each one.
 * prev_fd carries the read end of the previous pipe (-1 for the first).
 */
void	execute_pipeline(t_shell *shell)
{
	t_cmd	*cmd;
	int		pfd[2];
	int		prev_fd;
	int		last_pid;

	prev_fd = -1;
	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->next && pipe(pfd) == -1)
		{
			perror("minishell: pipe");
			return ;
		}
		if (!cmd->next)
			pfd[1] = -1;
		last_pid = fork_cmd(cmd, prev_fd, pfd, shell);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pfd[1]);
		prev_fd = pfd[0];
		cmd = cmd->next;
	}
	wait_children(last_pid, shell);
}
