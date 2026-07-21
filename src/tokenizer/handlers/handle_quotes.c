#include "minishell.h"

/*
** process_quoted_content
**
** This helper function extracts and processes the content inside
** quotes from the input string.
** - If the current character is the quote, store its type
**   (single or double).
** - Call extract_quoted_content() to get the text between the
**   opening and closing quotes.
** - If no content is found, return NULL.
** - If the quote type is double ("), expand variables inside the
**   quoted string using expand_variables().
** - The old quoted string is freed, and the expanded version is
**   used instead.
** - Return the final quoted string (allocated), or NULL on error.
*/
static char	*process_quoted_content(t_token_ctx *ctx)
{
	char	*quoted;
	char	*expanded;
	char	quote_type;

	if (!ctx->input[*ctx->i])
		return (NULL);
	quote_type = ctx->input[*ctx->i];
	quoted = extract_quoted_content(ctx->input, ctx->i, quote_type);
	if (!quoted)
		return (NULL);
	if (quote_type == '"' && !is_heredoc_delimiter(ctx))
	{
		expanded = expand_variables(quoted, ctx->shell);
		free(quoted);
		if (!expanded)
			return (NULL);
		quoted = expanded;
	}
	return (quoted);
}

/*
** add_quoted_token
**
** This function handles a token that starts with quotes.
** - Calls process_quoted_content() to extract the quoted text
**   and handle escapes if needed.
** - If extraction fails, return 0 (error).
** - The quoted string may be joined to the last word token:
**     * If result is 1, it was successfully joined -> return 1.
**     * If result is -1, an error occurred -> return 0.
** - Otherwise, create a new TK_WORD token with the quoted string
**   and add it to the token list.
** - The quoted string is then freed, and the function returns 1.
*/
int	add_quoted_token(t_token_ctx *ctx)
{
	char	*quoted;
	int		merge_res;

	quoted = process_quoted_content(ctx);
	if (!quoted)
		return (0);
	merge_res = join_to_last_token(ctx, quoted);
	if (merge_res == 1)
	{
		get_last_token(*(ctx->tokens))->is_quoted = 1;
		free(quoted);
		return (1);
	}
	if (merge_res == -1)
	{
		free(quoted);
		return (0);
	}
	add_token_to_list(ctx->tokens, new_token(quoted, TK_WORD, 1));
	free(quoted);
	return (1);
}
