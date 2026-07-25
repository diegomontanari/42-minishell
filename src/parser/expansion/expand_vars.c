/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:33:25 by pscarcin          #+#    #+#             */
/*   Updated: 2026/07/23 18:33:26 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** expand_environment_variable
**
** This function expands a standard environment variable inside
** a string.
** - Parameters:
**     * full_str   : the full input string containing the variable.
**     * start : index of the '$' character.
**     * end   : index where the variable name ends.
**     * shell : structure containing the environment list.
** - Retrieve the variable's value using get_variable_value().
** - Extract "prefix" (substring prefix '$') and "suffix"
**   (substring after the variable).
** - Build the new_str string: prefix + val + suffix.
** - Free temporary strings prefix returning.
** - Return the new new_str string, or NULL on failure.
*/
char	*expand_environment_variable(char *full_str, int dollar_pos, int end,
									t_shell *shell)
{
	char	*val;
	char	*prefix;
	char	*suffix;
	char	*final_str;

	val = get_variable_value(full_str, dollar_pos, end, shell);
	if (!val)
		return (NULL);
	prefix = ft_substr(full_str, 0, dollar_pos);
	suffix = ft_strdup(full_str + end);
	if (!prefix || !suffix)
		return (free_multiple_ptrs(val, prefix, suffix), NULL);
	final_str = expand_join_parts(prefix, val, suffix);
	return (free_multiple_ptrs(val, prefix, suffix), final_str);
}

/*
** process_dollar_sign
**
** This helper function expands a variable starting with '$'.
** - If '$' is the last character, no expansion is done and the
**   original string is returned.
** - If the next char is '?', expand to the shell's last exit code.
** - If the next char is '0', expand to the program name.
** - If the next char is alphabetic or '_', expand it as an
**   environment variable. The variable end is found using
**   expand_find_end_index().
** - If expansion fails, return the original string unchanged.
** - If expansion succeeds, free the old input and return the
**   newly expanded string.
*/
static char	*process_dollar_sign(char *input, int pos, t_shell *shell)
{
	char	*new_str;

	new_str = NULL;
	if (input[pos + 1] == '\0')
		return (input);
	if (input[pos + 1] == '?')
		new_str = expand_exit_status(input, pos, shell);
	else if (input[pos + 1] == '0')
		new_str = expand_program_name(input, pos, shell);
	else if (ft_isalpha(input[pos + 1]) || input[pos + 1] == '_')
		new_str = expand_environment_variable(input, pos,
				expand_find_end_index(input, pos), shell);
	else
		return (input);
	if (!new_str)
		return (NULL);
	return (free(input), new_str);
}

static int	expansion_token_len(char *input, int pos)
{
	if (input[pos + 1] == '?' || input[pos + 1] == '0')
		return (2);
	if (ft_isalpha(input[pos + 1]) || input[pos + 1] == '_')
		return (expand_find_end_index(input, pos) - pos);
	return (1);
}

/*
** expand_variables
**
** This function expands environment variables in the input string.
** - If input is NULL, return NULL immediately.
** - Duplicate the input string into result to work on a copy.
** - Iterate through each character of result:
**     * If a '$' is found and followed by another character,
**       call process_dollar_sign() to handle variable expansion.
**     * If process_dollar_sign() returns a new string, replace
**       result with it and restart from the same position.
** - Continue until the full string has been checked.
** - Return the final expanded string, or NULL on failure.
*/
static int	expand_process_iter(char **result, int *i, t_shell *shell)
{
	char	*temp;
	int		old_len;
	int		token_len;

	if ((*result)[*i] != '$')
		return (0);
	if ((*result)[*i + 1] == '\0')
		return (0);
	old_len = (int)ft_strlen(*result);
	token_len = expansion_token_len(*result, *i);
	temp = process_dollar_sign(*result, *i, shell);
	if (!temp)
	{
		free(*result);
		*result = NULL;
		return (-1);
	}
	if (temp == *result)
		return (0);
	*result = temp;
	*i += (int)ft_strlen(temp) - old_len + token_len;
	return (1);
}

/*
** expand_variables
**
** This function expands environment variables in the input string.
*/
char	*expand_variables(char *input, t_shell *shell)
{
	char	*result;
	int		i;
	int		status;

	if (!input)
		return (NULL);
	result = ft_strdup(input);
	if (!result)
		return (NULL);
	i = 0;
	while (result && result[i])
	{
		status = expand_process_iter(&result, &i, shell);
		if (status == -1)
			return (NULL);
		if (status == 0)
			i++;
	}
	return (result);
}
