#ifndef PARSER_H
# define PARSER_H

/* ── Redirection types ───────────────────────────────────────────────── */
/*
 * Mirrors the redirection token types but lives on t_redir nodes after
 * parsing. Pipes are not included: they split the command list instead
 * of being stored as redirections.
 */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

/* ── t_redir ─────────────────────────────────────────────────────────── */
/*
 * One redirection attached to a command node.
 * A command can have multiple redirections applied in order,
 * stored as a linked list. The last one for each fd wins.
 *
 * file : target filename for <, >, >>; delimiter string for <<.
 *        Heap-allocated; freed with the command list.
 * type : kind of redirection (see e_redir_type above).
 * next : next redirection for the same command, NULL if last.
 */
typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	struct s_redir	*next;
}	t_redir;

/* ── t_cmd ───────────────────────────────────────────────────────────── */
/*
 * One simple command in a pipeline, produced by the parser.
 * The parser converts the flat token list into a linked list of t_cmd,
 * one node per segment separated by pipes.
 *
 * args  : NULL-terminated array of strings, argv-style.
 *         args[0] is the command name, the rest are its arguments.
 *         Passed directly to execve() for external commands.
 * redirs: linked list of redirections to apply before executing.
 * next  : next command in the pipeline, NULL if last.
 */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* ── Forward declarations ────────────────────────────────────────────── */

typedef struct s_token		t_token;
typedef struct s_shell		t_shell;

/* ── Public parser interface ─────────────────────────────────────────── */

int		parse(t_shell *shell);
t_cmd	*new_cmd(void);

/* ── Internal parser functions ───────────────────────────────────────── */
/*
 * Used across multiple .c files inside the parser module.
 * is_redir  : returns 1 if token type is a redirection.
 * add_redir : creates a redir node, attaches it, advances token.
 * add_arg   : appends a string to the command's args array.
 */

int		is_redir(t_token_type type);
int		add_redir(t_cmd *cmd, t_token **tok);
int		add_arg(t_cmd *cmd, char *value);

#endif
