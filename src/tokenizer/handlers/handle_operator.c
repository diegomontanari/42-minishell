/* ************************************************************************** */
/*                                                                            */
/*   handle_operator.c                                                        */
/*                                                                            */
/*   Recognises the five operator tokens: |, <, >, <<, >>.                  */
/*   Double-char operators are checked first so < does not consume <<.      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Returns 1 if c is an operator character, 0 otherwise.
 * Used by the tokenizer to decide whether to dispatch to
 * handle_operator or handle_word.
 */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
 * Reads an operator token starting at line[*i] and advances *i past it.
 * Double-char operators (<< and >>) are checked before their single-char
 * counterparts so the longer match always wins.
 */
t_token	*handle_operator(char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (new_token("|", TOKEN_PIPE));
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i += 2;
		return (new_token("<<", TOKEN_HEREDOC));
	}
	if (line[*i] == '<')
	{
		(*i)++;
		return (new_token("<", TOKEN_REDIR_IN));
	}
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i += 2;
		return (new_token(">>", TOKEN_REDIR_APPEND));
	}
	(*i)++;
	return (new_token(">", TOKEN_REDIR_OUT));
}
