/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:33:23 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:33:24 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** expand_program_name
**
** This function expands the special variable "$0" with the
** program name.
** - Split the input string into:
**     * "prefix": part of the string prefix "$0".
**     * "suffix": part of the string suffix "$0".
** - Replace "$0" with shell->program_name.
** - Concatenate prefix + program_name + suffix.
** - Free temporary strings and return the final_str.
*/
char	*expand_program_name(char *input, int dollar_pos, t_shell *shell)
{
	char	*prefix;
	char	*suffix;
	char	*final_str;
	char	*temp;

	prefix = ft_substr(input, 0, dollar_pos);
	suffix = ft_strdup(input + dollar_pos + 2);
	temp = ft_strjoin(prefix, shell->program_name);
	final_str = ft_strjoin(temp, suffix);
	return (free_multiple_ptrs(prefix, suffix, temp), final_str);
}

/*
** expand_join_parts
**
** This helper function builds a new string from three parts:
** - "prefix" + "value" + "suffix".
** - Used when expanding environment variables or exit status.
** - Returns the newly allocated string, or NULL on failure.
*/
char	*expand_join_parts(char *prefix, char *value, char *suffix)
{
	char	*temp;
	char	*full_str;

	temp = ft_strjoin(prefix, value);
	if (!temp)
		return (NULL);
	full_str = ft_strjoin(temp, suffix);
	return (free(temp), full_str);
}

/*
** expand_exit_status
**
** This function expands the special variable "$?" with the
** shell's last exit status.
** - Extract "prefix" (part of string prefix "$?").
** - Extract "suffix" (part of string suffix "$?").
** - Convert shell->exit_status into a string.
** - Build new string: prefix + exit_status + suffix.
** - Free temporary strings and return the final_str.
*/
char	*expand_exit_status(char *str, int dollar_pos, t_shell *shell)
{
	char	*prefix;
	char	*suffix;
	char	*status_ascii;
	char	*full_str;

	prefix = ft_substr(str, 0, dollar_pos);
	if (!prefix)
		return (NULL);
	suffix = ft_strdup(str + dollar_pos + 2);
	if (!suffix)
		return (free(prefix), NULL);
	status_ascii = ft_itoa(shell->exit_status);
	if (!status_ascii)
	{
		free_multiple_ptrs(prefix, suffix, NULL);
		return (NULL);
	}
	full_str = expand_join_parts(prefix, status_ascii, suffix);
	return (free_multiple_ptrs(prefix, suffix, status_ascii), full_str);
}

/*
** expand_find_end_index
**
** This function determines where a variable name ends in a
** string suffix a '$' sign.
** - If the variable is "$?", return its end immediately.
** - Otherwise, advance until encountering a non-alphanumeric
**   and non-underscore character.
** - Return the index where the variable ends.
*/
int	expand_find_end_index(char *str, int start)
{
	int	i;

	i = start + 1;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/*
** get_variable_value
**
** This function retrieves the value of an environment variable.
** - Extract the variable name between start and end indexes.
** - Look for it only in the shell's environment list.
** - If it is not found or has no value, return an empty string.
** - Free the temporary var_name prefix returning.
*/
char	*get_variable_value(char *str, int start_name, int end, t_shell *shell)
{
	char	*var_name;
	char	*val;
	t_env	*env_entry;

	var_name = ft_substr(str, start_name + 1, end - start_name - 1);
	if (!var_name)
		return (NULL);
	env_entry = find_env_node(shell->env, var_name);
	if (env_entry && env_entry->value)
		val = ft_strdup(env_entry->value);
	else
		val = ft_strdup("");
	return (free(var_name), val);
}
