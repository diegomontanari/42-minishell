/* ************************************************************************** */
/*                                                                            */
/*   child.c                                                                  */
/*                                                                            */
/*   Code that runs inside each forked child process.                         */
/*   Wires stdin/stdout to the correct pipe ends, applies redirections,       */
/*   then either runs a builtin or calls execve for an external command.      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Connects prev_fd to stdin and pfd[1] to stdout, then closes unused fds. */
static void	setup_pipes(int prev_fd, int pfd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pfd[1] != -1)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	if (pfd[0] != -1)
		close(pfd[0]);
}

/* Prints an error and exits with 127 (command not found). */
static void	cmd_not_found(char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

/* Runs execve with the resolved path and converted env array. */
static void	run_execve(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	path = find_path(cmd->args[0], shell->env);
	if (!path)
		cmd_not_found(cmd->args[0]);
	envp = env_to_array(shell->env);
	if (!envp)
	{
		free(path);
		exit(1);
	}
	execve(path, cmd->args, envp);
	perror("minishell");
	free(path);
	free_split(envp);
	exit(126);
}

/*
 * Full child process setup: signals, pipes, redirections, then exec.
 * If the command is a builtin inside a pipeline, run it and exit.
 */
void	exec_child(t_cmd *cmd, int prev_fd, int pfd[2],
		t_shell *shell)
{
	signals_child();
	setup_pipes(prev_fd, pfd);
	apply_redirs(cmd->redirs, shell);
	if (is_builtin(cmd))
		exit(execute_builtin(cmd, shell));
	if (!cmd->args[0])
		exit(0);
	run_execve(cmd, shell);
}
