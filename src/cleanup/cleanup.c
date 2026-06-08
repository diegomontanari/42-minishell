/* ************************************************************************** */
/*                                                                            */
/*   cleanup.c                                                                */
/*                                                                            */
/*   Frees all heap memory owned by the shell at the end of each cycle.     */
/*   free_tokens  : frees the token linked list.                             */
/*   free_redirs  : frees the redirection list of one command.               */
/*   free_cmds    : frees the full command linked list.                      */
/*   free_env     : frees the environment variable linked list.              */
/*   cleanup_shell: frees line, tokens and cmds after each command cycle.   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Frees the full token linked list produced by the tokenizer.
 * Iterates the list, frees value and then the node itself.
 * Safe to call with NULL — returns immediately without dereferencing.
 */
void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

/*
 * Frees the redirection list attached to a single command node.
 * Iterates the list, frees file and then the node itself.
 * Safe to call with NULL.
 */
void	free_redirs(t_redir *redirs)
{
	t_redir	*next;

	while (redirs)
	{
		next = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = next;
	}
}

/*
 * Frees the full command linked list produced by the parser.
 * For each node: frees the args array element by element, then the
 * array itself, then the redirs list, then the node.
 * Safe to call with NULL.
 */
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;
	int		i;

	while (cmds)
	{
		next = cmds->next;
		i = 0;
		while (cmds->args && cmds->args[i])
			free(cmds->args[i++]);
		free(cmds->args);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = next;
	}
}

/*
 * Frees the environment variable linked list.
 * For each node: frees key, frees value (can be NULL), frees the node.
 * Safe to call with NULL.
 */
void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

/*
 * Frees all per-cycle allocations: the raw input line, the token list,
 * and the command list. Does not free env — it persists across cycles.
 * Resets the three pointers to NULL so the next cycle starts clean.
 */
void	cleanup_shell(t_shell *shell)
{
	free(shell->line);
	shell->line = NULL;
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free_cmds(shell->cmds);
	shell->cmds = NULL;
}
