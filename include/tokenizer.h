#ifndef TOKENIZER_H
# define TOKENIZER_H

/* ── Token types ─────────────────────────────────────────────────────── */
/*
 * Enum used by the tokenizer to tag each token with its syntactic role.
 * TOKEN_WORD        : a plain word, command name, or argument.
 * TOKEN_PIPE        : the | operator connecting two commands.
 * TOKEN_REDIR_IN    : < redirect stdin from file.
 * TOKEN_REDIR_OUT   : > redirect stdout to file (truncate).
 * TOKEN_REDIR_APPEND: >> redirect stdout to file (append).
 * TOKEN_HEREDOC     : << read stdin until delimiter.
 */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

/* ── t_token ─────────────────────────────────────────────────────────── */
/*
 * A single unit produced by the tokenizer from the raw input string.
 * Tokens form a singly-linked list consumed by the parser.
 *
 * value : the raw string of the token (e.g. "ls", "|", "file.txt").
 *         Heap-allocated; must be freed when the list is destroyed.
 * type  : syntactic role assigned during tokenization.
 * next  : pointer to the following token, NULL if last.
 */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* ── Forward declaration ─────────────────────────────────────────────── */
/*
 * t_shell is defined in minishell.h which includes this file.
 * A forward declaration is enough here because tokenize() only
 * takes a pointer to it; the compiler does not need the full layout.
 */
typedef struct s_shell	t_shell;

/* ── Public tokenizer interface ──────────────────────────────────────── */

t_token	*tokenize(char *line, t_shell *shell);
t_token	*new_token(char *value, t_token_type type);

/* ── Internal tokenizer functions ────────────────────────────────────── */
/*
 * Used across multiple .c files inside the tokenizer module.
 * is_operator   : returns 1 if c is |, < or >.
 * handle_operator: reads an operator token and advances the index.
 * handle_word   : reads a word token (with quotes) and advances.
 */

int		is_operator(char c);
t_token	*handle_operator(char *line, int *i);
t_token	*handle_word(char *line, int *i);

#endif
