/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:34:14 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:34:15 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** process_next_token
**
** This helper function processes the next token in the input.
** - Reads the current character at the index from context.
** - If it is a single or double quote, call handle_quoted_token().
** - If it is a redirection symbol ('<' or '>'), call
**   handle_redirection_token() to parse it.
** - If it is a pipe ('|'), create a pipe token and add it to
**   the token list, then advance the index.
** - Otherwise, handle_word_token() is called to process a word.
** - Always returns 1 to indicate the function finished its job.
*/
static int	process_next_token(t_token_ctx *ctx)
{
	char	c;
	char	*token_str;
	int		i;

	i = *(ctx->i);
	c = ctx->input[i];
	if (c == '\'' || c == '"')
		return (add_quoted_token(ctx));
	if (c == '<' || c == '>')
		add_redir_token(ctx);
	else if (c == '|')
	{
		token_str = ft_strdup("|");
		add_token_to_list(ctx->tokens,
			new_token(token_str, TK_PIPE, 0));
		free(token_str);
		(*(ctx->i))++;
	}
	else
		add_word_token(ctx);
	return (1);
}

/*
** run_tokenization_loop
**
** This helper function performs the main tokenization loop.
** - It repeatedly skips whitespace and checks if more input is
**   available.
** - The has_space flag is updated in the context to indicate
**   whether whitespace appeared before the next token.
** - For each iteration, process_next_token() is called to extract
**   and store the next token.
** - If token processing fails, return 0 to signal an error.
** - When all tokens are processed successfully, return 1.
*/
static int	run_tokenization_loop(t_token_ctx *ctx, int *has_space)
{
	while (skip_spaces_and_check(ctx->input,
			ctx->i, has_space))
	{
		ctx->has_space = *has_space;
		if (!process_next_token(ctx))
			return (0);
		*has_space = 0;
	}
	return (1);
}

/*
** parse_line_to_tokens
**
** This function parses a command line into a list of tokens.
** - It initializes a token context with the input string, index,
**   token list pointer, and shell reference.
** - The variable has_space tracks if whitespace was found
**   before a token (used for correct parsing).
** - It calls run_tokenization_loop() to process the input and
**   generate tokens.
** - If tokenization fails, all allocated tokens are freed and
**   NULL is returned.
** - On success, return the head of the token list.
*/
t_token	*parse_line_to_tokens(const char *str, t_shell *shell)
{
	t_token_ctx		ctx;
	t_token			*tokens;
	int				i;
	int				has_space;

	tokens = NULL;
	i = 0;
	has_space = 1;
	ctx.input = str;
	ctx.i = &i;
	ctx.tokens = &tokens;
	ctx.shell = shell;
	if (!run_tokenization_loop(&ctx, &has_space))
		return (clear_token_list(&tokens), NULL);
	return (tokens);
}
