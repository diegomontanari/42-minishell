#ifndef CLEANUP_H
# define CLEANUP_H

/* ── Forward declarations ────────────────────────────────────────────── */
/*
 * All types below are defined in the sub-headers and minishell.h that
 * precede cleanup.h in the include chain. Forward declarations cover
 * the case where cleanup.h is included standalone.
 */
typedef struct s_token	t_token;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;
typedef struct s_shell	t_shell;

/* ── free_tokens ─────────────────────────────────────────────────────── */
/*
 * Frees the full token linked list produced by the tokenizer.
 * Each node's value string is freed before the node itself.
 * Safe to call with NULL.
 */
void	free_tokens(t_token *tokens);

/* ── free_redirs ─────────────────────────────────────────────────────── */
/*
 * Frees the redirection list attached to a single command node.
 * Each node's file string is freed before the node itself.
 * Safe to call with NULL.
 */
void	free_redirs(t_redir *redirs);

/* ── free_cmds ───────────────────────────────────────────────────────── */
/*
 * Frees the full command linked list produced by the parser.
 * For each node: frees args array, frees redirs list, frees the node.
 * Safe to call with NULL.
 */
void	free_cmds(t_cmd *cmds);

/* ── free_env ────────────────────────────────────────────────────────── */
/*
 * Frees the environment variable linked list.
 * Each node's key and value strings are freed before the node itself.
 * Safe to call with NULL.
 */
void	free_env(t_env *env);

/* ── cleanup_shell ───────────────────────────────────────────────────── */
/*
 * Frees all heap memory owned by the shell context at the end of each
 * command cycle: line, tokens, cmds. Does not free env (persists
 * across cycles) or the shell struct itself (stack-allocated in main).
 */
void	cleanup_shell(t_shell *shell);

#endif
