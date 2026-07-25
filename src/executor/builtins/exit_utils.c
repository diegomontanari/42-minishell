/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:31:48 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:31:49 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts how many leading whitespace characters are in a string.
*/
int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

static int	is_exit_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

static int	number_overflows(char *str, int i, unsigned long limit)
{
	unsigned long	result;
	unsigned long	digit;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = (unsigned long)(str[i] - '0');
		if (result > (limit - digit) / 10)
			return (1);
		result = result * 10 + digit;
		i++;
	}
	return (0);
}

/*
** Validates if a string can be safely converted to a long
** without overflow.
*/
int	check_atol_conversion(char *str)
{
	unsigned long	limit;
	int				i;

	if (!str)
		return (1);
	i = 0;
	while (is_exit_space(str[i]))
		i++;
	limit = (unsigned long)LONG_MAX;
	if (str[i] == '-')
		limit++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (number_overflows(str, i, limit));
}

/*
** Checks if a string represents a valid numeric value.
*/
int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (is_exit_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (is_exit_space(str[i]))
		i++;
	return (str[i] == '\0');
}
