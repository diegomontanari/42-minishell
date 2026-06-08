/* ************************************************************************** */
/*                                                                            */
/*   builtin_export.c                                                         */
/*                                                                            */
/*   With no arguments: prints all env vars in "declare -x" format.           */
/*   With arguments: adds or updates variables in the environment list.       */
/*   Validation and node lookup are in builtin_export_utils.c.                */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* Prints all env vars in declare -x format (export with no args). */
static void	print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		env = env->next;
	}
}

/* Extracts the key portion from "KEY=VALUE" or duplicates the whole arg. */
static char	*extract_key(char *arg, char *eq)
{
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

/* Processes one export argument like "KEY=VALUE" or "KEY". */
static int	export_one(char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;
	t_env	*node;

	eq = ft_strchr(arg, '=');
	key = extract_key(arg, eq);
	if (!valid_identifier(key))
	{
		export_error(arg);
		free(key);
		return (1);
	}
	node = find_or_create(key, shell);
	free(key);
	if (!node)
		return (1);
	if (eq)
	{
		free(node->value);
		node->value = ft_strdup(eq + 1);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
	{
		print_export(shell->env);
		return (0);
	}
	ret = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if (export_one(cmd->args[i], shell) != 0)
			ret = 1;
	}
	return (ret);
}
