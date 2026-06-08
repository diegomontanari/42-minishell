/* ************************************************************************** */
/*                                                                            */
/*   parser.c                                                                 */
/*                                                                            */
/*   Converts the flat token list into a linked list of t_cmd nodes.         */
/*   Each pipe token splits the list into a new command segment.             */
/*   Redirections are extracted and attached to the current command.          */
/*   Everything else becomes an argument in the command's args array.         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Allocates and zero-initialises a new t_cmd node.
 * Returns NULL if malloc fails.
 */
t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
 * Dispatches a single token to the correct handler.
 * PIPE : creates a new command node and advances cmd.
 * REDIR: creates a redir node and advances tok past the filename.
 * WORD : appends the value to the current command's args.
 * Returns 0 on success, -1 on allocation failure.
 */
static int	process_token(t_cmd **cmd, t_token **tok)
{
	if ((*tok)->type == TOKEN_PIPE)
	{
		(*cmd)->next = new_cmd();
		if (!(*cmd)->next)
			return (-1);
		*cmd = (*cmd)->next;
	}
	else if (is_redir((*tok)->type))
	{
		if (add_redir(*cmd, tok) < 0)
			return (-1);
	}
	else
	{
		if (add_arg(*cmd, (*tok)->value) < 0)
			return (-1);
	}
	return (0);
}

/*
 * Main parser entry point. Walks the token list stored in shell->tokens
 * and builds a linked list of t_cmd stored in shell->cmds.
 * Returns 0 on success, -1 on allocation failure or syntax error.
 */
int	parse(t_shell *shell)
{
	t_token	*tok;
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (-1);
	shell->cmds = cmd;
	tok = shell->tokens;
	while (tok)
	{
		if (process_token(&cmd, &tok) < 0)
			return (-1);
		tok = tok->next;
	}
	return (0);
}
