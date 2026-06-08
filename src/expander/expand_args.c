/* ************************************************************************** */
/*                                                                            */
/*   expand_args.c                                                            */
/*                                                                            */
/*   Public interface: expands variables in all args of all commands.          */
/*   Also expands filenames in redirections.                                   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Expands $VAR and $? in a string, returning a new heap string. */
char	*expand_str(char *str, t_shell *shell)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
			res = exp_append_var(res, str, &i, shell);
		else
			res = exp_append_char(res, str[i++]);
	}
	return (res);
}

/* Expands redir filenames for one command. */
static void	expand_redirs(t_redir *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
		{
			expanded = expand_str(redir->file, shell);
			free(redir->file);
			redir->file = expanded;
		}
		redir = redir->next;
	}
}

/* Expands all args and redirs for every command in the list. */
void	expand_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;

	while (cmd)
	{
		i = -1;
		if (cmd->args)
		{
			while (cmd->args[++i])
			{
				expanded = expand_str(cmd->args[i], shell);
				free(cmd->args[i]);
				cmd->args[i] = expanded;
			}
		}
		expand_redirs(cmd->redirs, shell);
		cmd = cmd->next;
	}
}
