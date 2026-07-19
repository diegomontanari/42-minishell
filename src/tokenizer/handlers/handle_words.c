/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** extract_raw_word
**
** This function extracts a raw word starting at index *i.
** - Save the starting position.
** - Advance *i while the current character:
**     * is not null,
**     * is not a space,
**     * is not a separator (like |, <, >),
**     * is not a single or double quote.
** - Calculate the length of the word.
** - If length is 0 or less, return NULL (no word found).
** - Otherwise, return a new substring from start to *i.
*/
char	*extract_raw_word(const char *input, int *i)
{
	int		start;
	char	*word;
	int		len;

	start = *i;
	while (input[*i] && input[*i] != ' ' && !is_separator(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (NULL);
	word = ft_substr(input, start, *i - start);
	return (word);
}
/*
** extract_and_expand_word
**
** This function extracts a raw word from the input and applies
** variable expansion.
*/

char	*extract_and_expand_word(const char *input, int *i, t_shell *shell)
{
	char	*word;
	char	*expanded;

	word = extract_raw_word(input, i);
	if (!word)
		return (NULL);
	expanded = expand_variables(word, shell);
	free(word);
	return (expanded);
}

/*
** add_word_token
**
** This function processes a word token from the input.
** - Calls extract_and_expand_word() to read the word and expand
**   any variables if present.
** - If extraction fails, return immediately.
** - If the word can be joined to the previous word token,
**   join it and return.
** - Otherwise, create a new TK_WORD token with the expanded word
**   and add it to the token list.
** - Free the temporary expanded string after adding the token.
*/
void	add_word_token(t_token_ctx *ctx)
{
	char	*expanded;
	int		merge_res;

	expanded = extract_and_expand_word(ctx->input, ctx->i, ctx->shell);
	if (!expanded)
		return ;
	merge_res = join_to_last_token(ctx, expanded);
	if (merge_res == 1)
	{
		free(expanded);
		return ;
	}
	add_token_to_list(ctx->tokens, new_token(expanded, TK_WORD, 0));
	free(expanded);
}
