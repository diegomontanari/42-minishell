/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if a string is a valid shell variable identifier.
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** Extracts the key (variable name) from an environment
** string in the form "KEY=VALUE".
*/
char	*extract_key(char *str)
{
	char	*eq_position;
	int		key_len;

	eq_position = ft_strchr(str, '=');
	if (!eq_position)
		return (ft_strdup(str));
	key_len = eq_position - str;
	return (ft_substr(str, 0, key_len));
}

/*
** Extracts the value part from an environment string in
** the form "KEY=VALUE".
*/
char	*extract_value(char *str)
{
	char	*eq_position;

	eq_position = ft_strchr(str, '=');
	if (!eq_position)
		return (NULL);
	return (ft_strdup(eq_position + 1));
}
