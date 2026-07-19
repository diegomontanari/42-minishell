#include "minishell.h"

/*
** clear_token_list (was clear_token_list)
** Frees all nodes in a linked list of tokens.
*/
void	clear_token_list(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = tmp;
	}
}

/*
** free_cmd
** Frees a single command structure and its associated data.
*/
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->path)
		free(cmd->path);
	if (cmd->tokens)
		clear_token_list(&cmd->tokens);
	free(cmd);
}

/*
** clear_cmd_list (was clear_cmd_list)
** Frees all nodes in a linked list of commands.
*/
void	clear_cmd_list(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *cmds;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
	*cmds = NULL;
}
