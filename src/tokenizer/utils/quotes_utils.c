#include "minishell.h"

/*
** has_unclosed_quotes
**
** This function checks if a string ends with unclosed quotes.
** - It loops through each character of the string.
** - If inside double quotes, a backslash followed by another char
**   is skipped to handle escape sequences.
** - If a single quote is found and not inside double quotes, toggle
**   the single_open flag.
** - If a double quote is found and not inside single quotes, toggle
**   the double_open flag.
** - At the end, return true if either single or double quotes are
**   still open (unclosed).
*/
int	has_unclosed_quotes(const char *str)
{
	int		i;
	int		single_open;
	int		double_open;

	i = 0;
	single_open = 0;
	double_open = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (str[i] == '"' && !single_open)
			double_open = !double_open;
		i++;
	}
	return (single_open || double_open);
}
/* ALTERNATIVA SENZA CONTINUE
 
int	has_unclosed_quotes(const char *str)
{
	int	i;
	int	single_open;
	int	double_open;

	i = 0;
	single_open = 0;
	double_open = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && double_open)
		{
			i += 2;
		}
		else
		{
			if (str[i] == '\'' && !double_open)
				single_open = !single_open;
			else if (str[i] == '"' && !single_open)
				double_open = !double_open;
			i++;
		}
	}
	return (single_open || double_open);
}

*/

/*
** extract_quoted_content
**
** This function extracts the content inside quotes from a string.
*/
static int	find_closing_quote(const char *str, int start, char quote_char)
{
	int	i;

	i = start;
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] != quote_char)
		return (-1);
	return (i);
}

char	*extract_quoted_content(const char *str, int *index, char quote_char)
{
	int		start;
	int		end;
	char	*quoted;
	int		i;

	i = *index;
	if (str[i] == quote_char)
		i++;
	start = i;
	end = find_closing_quote(str, start, quote_char);
	if (end == -1)
	{
		*index = ft_strlen(str);
		return (NULL);
	}
	quoted = ft_substr(str, start, end - start);
	*index = end + 1;
	return (quoted);
}
