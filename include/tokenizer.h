#ifndef TOKENIZER_H
# define TOKENIZER_H

// We assume t_shell is typedef'd before including this file,
// or we use struct s_shell.
// To ensure standalone validity if needed,
// we can forward declare struct s_shell.
struct	s_shell;

//  TOKEN TYPES & STRUCTS
// t_token_types: tipi di token generati dal tokenizer.

typedef enum e_token_types
{
	TK_WORD,
	TK_PIPE,
	TK_OUT,
	TK_APPEND,
	TK_IN,
	TK_HEREDOC,
	TK_EOF
}	t_token_types;

// struct s_token: nodo della lista di token.

typedef struct s_token
{
	char			*value;
	int				type;
	int				is_quoted;
	struct s_token	*next;
}	t_token;

// t_token_ctx: contesto per operazioni di parsing dei token.
typedef struct s_token_ctx
{
	const char		*input; // Stringa di input da parsare
	int				*i; // Indice per la posizione corrente nella stringa
	t_token			**tokens; // Lista di token generati
	struct s_shell	*shell; // accesso allo stato "globale"
	int				has_space; // Flag per indicare se c'è spazio tra i token
}	t_token_ctx;

//  1) LINE CONSTRUCTION

t_token		*parse_line_to_tokens(const char *str, struct s_shell *shell);
char		*get_full_line(char *initial_input);

// 2) PARSING HELPERS

int			skip_spaces_and_check(const char *str, int *i,
				int *has_space);
int			is_separator(char c);
char		*extract_quoted_content(const char *str, int *index,
				char quote_char);

//  3) TOKEN CREATION

void		add_redir_token(t_token_ctx *ctx);
int			add_quoted_token(t_token_ctx *context);
void		add_word_token(t_token_ctx *context);

// 4) TOKEN LIST OPS

t_token		*new_token(char *value, int type, int is_quoted);
int			join_to_last_token(t_token_ctx *ctx, char *new_text);
void		add_token_to_list(t_token **head, t_token *new_token);
t_token		*get_last_token(t_token *head);

#endif
