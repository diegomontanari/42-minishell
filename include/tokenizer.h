/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:30:27 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:30:28 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/* Forward declaration */
struct	s_shell;

/* TOKEN TYPES AND STRUCTS */

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

/* Token list node */

typedef struct s_token
{
	char			*value;
	int				type;
	int				is_quoted;
	int				heredoc_fd;
	struct s_token	*next;
}	t_token;

/* Tokenizer context */
typedef struct s_token_ctx
{
	const char		*input;
	int				*i;
	t_token			**tokens;
	struct s_shell	*shell;
	int				has_space;
}	t_token_ctx;

/* 1) LINE CONSTRUCTION */

t_token		*parse_line_to_tokens(const char *str, struct s_shell *shell);
char		*get_full_line(char *initial_input);

/* 2) PARSING HELPERS */

int			skip_spaces_and_check(const char *str, int *i,
				int *has_space);
int			is_separator(char c);
char		*extract_quoted_content(const char *str, int *index,
				char quote_char);

/* 3) TOKEN CREATION */

void		add_redir_token(t_token_ctx *ctx);
int			add_quoted_token(t_token_ctx *context);
void		add_word_token(t_token_ctx *context);

/* 4) TOKEN LIST OPERATIONS */

t_token		*new_token(char *value, int type, int is_quoted);
int			join_to_last_token(t_token_ctx *ctx, char *new_text);
int			is_heredoc_delimiter(t_token_ctx *ctx);
void		add_token_to_list(t_token **head, t_token *new_token);
t_token		*get_last_token(t_token *head);

#endif
