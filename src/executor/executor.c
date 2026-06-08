/* ************************************************************************** */
/*                                                                            */
/*   executor.c                                                               */
/*                                                                            */
/*   Entry point for command execution.                                       */
/*   Single builtin without pipes runs in the current process so it can       */
/*   modify shell state (cd, export, unset, exit). Everything else goes       */
/*   through the pipeline path which forks child processes.                   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Builtin names are compared case-sensitively, matching bash behaviour. */
static const char	*g_builtins[] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
};

/*
 * Checks if cmd->args[0] matches any builtin name.
 * Returns 1 if builtin, 0 otherwise.
 */
int	is_builtin(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	i = -1;
	while (g_builtins[++i])
	{
		if (ft_strlen(cmd->args[0]) == ft_strlen(g_builtins[i])
			&& ft_strncmp(cmd->args[0], g_builtins[i],
				ft_strlen(g_builtins[i])) == 0)
			return (1);
	}
	return (0);
}

/*
 * Dispatches to the matching builtin function.
 * Returns the builtin's exit status.
 */
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(name, "export", 7) == 0)
		return (builtin_export(cmd, shell));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strncmp(name, "env", 4) == 0)
		return (builtin_env(shell));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (builtin_exit(cmd, shell));
	return (1);
}

/*
 * Main execution entry point called by process_line.
 * Single builtin: runs in-process to let it change shell state.
 * Anything else: delegates to execute_pipeline (forks children).
 */
void	execute(t_shell *shell)
{
	if (!shell->cmds)
		return ;
	signals_executing();
	if (!shell->cmds->next && is_builtin(shell->cmds))
	{
		apply_redirs(shell->cmds->redirs, shell);
		shell->exit_status = execute_builtin(shell->cmds, shell);
		dup2(shell->stdin_backup, STDIN_FILENO);
		dup2(shell->stdout_backup, STDOUT_FILENO);
	}
	else
		execute_pipeline(shell);
	signals_interactive();
}
