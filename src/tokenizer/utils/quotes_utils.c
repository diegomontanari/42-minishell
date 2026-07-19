/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
