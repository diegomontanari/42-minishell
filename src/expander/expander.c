/* ************************************************************************** */
/*                                                                            */
/*   expander.c                                                               */
/*                                                                            */
/*   Expands $VAR and $? inside each command argument string.                 */
/*   Single-quoted strings are not expanded (handled by the tokenizer         */
/*   which preserves quote context via a flag).                               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Extracts the variable name starting at str[*i] (after the $). */
static char	*extract_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup(""));
	return (ft_substr(str, start, *i - start));
}

/* Resolves a variable name to its value string. */
static char	*resolve_var(char *name, t_shell *shell)
{
	char	*val;

	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(shell->exit_status));
	val = get_env_value(name, shell->env);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

/* Appends a single character to a heap string, returning new string. */
char	*exp_append_char(char *str, char c)
{
	char	buf[2];
	char	*res;

	buf[0] = c;
	buf[1] = '\0';
	res = ft_strjoin(str, buf);
	free(str);
	return (res);
}

/* Appends a resolved variable value to the result string. */
char	*exp_append_var(char *res, char *str, int *i,
		t_shell *shell)
{
	char	*name;
	char	*val;
	char	*tmp;

	(*i)++;
	name = extract_var_name(str, i);
	val = resolve_var(name, shell);
	tmp = ft_strjoin(res, val);
	free(res);
	free(name);
	free(val);
	return (tmp);
}
