/* ************************************************************************** */
/*                                                                            */
/*   handle_word.c                                                            */
/*                                                                            */
/*   Extracts a word token from the input string. A word is any sequence    */
/*   of characters that is not whitespace or an operator. Single and double  */
/*   quotes are consumed but not included in the token value: everything    */
/*   between matching quotes is taken literally as part of the word.         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Returns 1 if c ends a word: NUL, whitespace, or operator character.
 */
static int	is_word_end(char c)
{
	if (c == '\0' || c == ' ' || c == '\t')
		return (1);
	return (is_operator(c));
}

/*
 * Appends a single character to a heap-allocated string.
 * If str is NULL, allocates a new one-char string.
 * Returns the new string; the old one is freed.
 * Returns NULL on malloc failure.
 */
static char	*append_char(char *str, char c)
{
	char	buf[2];
	char	*result;

	buf[0] = c;
	buf[1] = '\0';
	if (!str)
		return (ft_strdup(buf));
	result = ft_strjoin(str, buf);
	free(str);
	return (result);
}

/*
 * Reads a word token starting at line[*i] and advances *i past it.
 * Handles single and double quotes: content between matching quotes
 * is added literally to the word without the quote characters.
 * If a closing quote is missing, reads until end of string.
 */
t_token	*handle_word(char *line, int *i)
{
	char	*word;
	char	quote;
	t_token	*tok;

	word = NULL;
	while (!is_word_end(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				word = append_char(word, line[(*i)++]);
			if (line[*i])
				(*i)++;
		}
		else
			word = append_char(word, line[(*i)++]);
	}
	if (!word)
		return (NULL);
	tok = new_token(word, TOKEN_WORD);
	free(word);
	return (tok);
}
