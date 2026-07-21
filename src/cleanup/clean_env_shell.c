#include "minishell.h"

/*
** clear_env_str (was clear_env_str)
** Frees all nodes in a linked list of environment variables.
*/
void	clear_env_str(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

/*
** free_env_node
** Frees a single environment variable node.
*/
void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free_multiple_ptrs(node->key, node->value, NULL);
	free(node);
}

/*
** reset_loop_state (was reset_loop_state)
** Frees all resources allocated during a single command
** execution, preparing the shell for the next prompt cycle.
*/
void	reset_loop_state(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->tokens)
	{
		clear_token_list(&shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		clear_cmd_list(&shell->cmds);
		shell->cmds = NULL;
	}
}

/*
** full_shell_cleanup (was full_shell_cleanup)
** Frees all resources associated with the shell before exit.
*/
void	full_shell_cleanup(t_shell *shell)
{
	if (!shell)
		return ;
	reset_loop_state(shell);
	if (shell->env)
	{
		clear_env_str(shell->env);
		shell->env = NULL;
	}
	if (shell->program_name)
	{
		free(shell->program_name);
		shell->program_name = NULL;
	}
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
}
