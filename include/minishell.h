#ifndef MINISHELL_H
# define MINISHELL_H

/* ── System includes ─────────────────────────────────────────────────── */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ── Project includes ────────────────────────────────────────────────── */
/*
 * Sub-headers are included here, at the top of the file, to satisfy
 * the Norm rule that all includes must precede other declarations.
 * Each sub-header owns its types: tokenizer.h defines t_token and
 * t_token_type; parser.h will define t_redir, t_cmd, t_redir_type.
 * Types used only inside this file (t_env, t_shell) are defined below.
 */

# include "../libft/libft.h"
# include "tokenizer.h"
# include "parser.h"
# include "executor.h"
# include "expander.h"
# include "cleanup.h"

/* ── Global signal variable ──────────────────────────────────────────── */
/*
 * The only global variable allowed by the subject.
 * Set exclusively inside signal handlers to communicate the received
 * signal number to the main loop. No other data must pass through here:
 * using a struct or storing shell state globally would violate the rules.
 * volatile sig_atomic_t guarantees safe read/write from signal context.
 */
extern volatile sig_atomic_t	g_signal;

/* ── t_env ───────────────────────────────────────────────────────────── */
/*
 * One node in the shell's environment variable list.
 * Stored as a linked list so export and unset can modify it at runtime
 * without reallocating a flat array on every change.
 *
 * key   : variable name (e.g. "PATH", "HOME"). Heap-allocated.
 * value : variable value (e.g. "/usr/bin:/bin"). Heap-allocated.
 *         NULL is valid: a variable can be exported without a value.
 * next  : next variable in the list, NULL if last.
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ── t_shell ─────────────────────────────────────────────────────────── */
/*
 * Central context struct passed to every function in the shell.
 * Holds all runtime state so no global variables are needed
 * beyond g_signal.
 *
 * line         : raw input string returned by readline().
 *                Freed after each command cycle.
 * tokens       : token list produced by the tokenizer from line.
 *                Freed after parsing builds the cmd list.
 * cmds         : command list produced by the parser from tokens.
 *                Freed after execution completes.
 * env          : live environment variable list.
 *                Persists across commands.
 * exit_status  : exit code of the last foreground command ($?).
 * stdin_backup : saved fd 0 before any redirection, restored after.
 * stdout_backup: saved fd 1 before any redirection, restored after.
 */
typedef struct s_shell
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	t_env	*env;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_shell;

/* ── Core function prototypes ────────────────────────────────────────── */

void	init_shell(t_shell *shell, char **envp);
void	shell_loop(t_shell *shell);
void	process_line(char *line, t_shell *shell);

/* ── Signal function prototypes ──────────────────────────────────────── */
/*
 * Three contexts require different signal behaviour.
 * Call the matching setup function at the start of each context.
 */

void	signals_interactive(void);
void	signals_executing(void);
void	signals_child(void);

/* ── Error handling ─────────────────────────────────────────────────── */

void	syntax_error(char *token);
int		check_syntax(t_token *tokens, t_shell *shell);

#endif
