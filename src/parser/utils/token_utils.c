#include "minishell.h"

/*
** only_spaces
**
** This function checks if a string contains only spaces or tabs.
** - Iterate through each character in the string.
** - If any character is not a space (' ') and not a tab ('\t'),
**   return 0 (false).
** - If the loop finishes without finding other characters,
**   return 1 (true).
*/
int	only_spaces(const char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
			return (0);
		s++;
	}
	return (1);
}

/*
** is_separator
**
** This function checks if a character is a token separator.
** - Returns 1 if the character is '|', '<', or '>'.
** - Returns 0 otherwise.
*/
int	is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** skip_spaces_and_check
**
** This function skips whitespace in the input string and checks
** if more characters remain.
** - It calls skip_spaces() starting from the current index.
** - If at least one space was skipped, set *has_space to 1.
** - The index *i is updated to the new position after skipping.
** - Returns 1 if the string has more characters to read,
**   or 0 if the end of the string is reached.
*/
int	skip_spaces_and_check(const char *s, int *i, int *has_space)
{
	int	skipped;

	skipped = skip_spaces(s + *i);
	if (skipped > 0)
		*has_space = 1;
	*i += skipped;
	return (s[*i] != '\0');
}

/*
** join_to_last_token
**
** This helper function attempts to merge new text with the previous token.
** - If whitespace was encountered (ctx->has_space), returns 0 (no merge).
** - Gets the last token. If it doesn't exist or isn't a WORD, returns 0.
** - Joins the last token's value with the new text.
** - Frees the old value and updates it with the merged one.
** - Returns 1 on success, -1 on allocation failure.
*/
int	join_to_last_token(t_token_ctx *ctx, char *append_str)
{
	t_token	*last;
	char	*joined;

	if (ctx->has_space)
		return (0);
	last = get_last_token(*(ctx->tokens));
	if (!last || last->type != TK_WORD)
		return (0);
	joined = ft_strjoin(last->value, append_str);
	if (!joined)
		return (-1);
	free(last->value);
	last->value = joined;
	return (1);
}
