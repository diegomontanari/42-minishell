/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cmd_extract_tokens
**
** This function extracts tokens for a single command until
** a pipe token (TK_PIPE) or end of list.
** - Allocate new tokens with create_token().
** - Link them into a new token list (head).
** - If allocation fails, free the partially built list.
** - Return the head of the new token list.
*/
static t_token	*cmd_extract_tokens(t_token *start)
{
	t_token	*head;
	t_token	*last_token;
	t_token	*curr;
	t_token	*new_node;

	head = NULL;
	last_token = NULL;
	curr = start;
	while (curr && curr->type != TK_PIPE)
	{
		new_node = new_token(curr->value, curr->type, curr->is_quoted);
		if (!new_node)
		{
			clear_token_list(&head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			last_token->next = new_node;
		last_token = new_node;
		curr = curr->next;
	}
	return (head);
}

/*
** cmd_resolve_path
**
** This function determines whether a command is a builtin
** or an external command.
** - If args is empty, return 1 (invalid command).
** - If the command is builtin:
**     * Set type = CMD_BUILTIN.
**     * Path is set to NULL.
** - Otherwise:
**     * Set type = CMD_EXTERNAL.
**     * Find the command path with find_command_path().
**     * If path not found, reset_loop_state() is called
**       and path is set to NULL.
** - Always return 1.
*/
static int	cmd_resolve_path(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		cmd->type = CMD_BUILTIN;
		cmd->path = NULL;
	}
	else
	{
		cmd->type = CMD_EXTERNAL;
		cmd->path = find_command_path(cmd->args[0], shell);
	}
	return (1);
}

/*
** cmd_create
**
** This function creates and initializes a new command struct.
** - Allocate a new t_cmd with create_new_cmd().
** - Extract tokens for this command with cmd_extract_tokens().
** - Convert tokens into args using prepare_cmd_args().
** - If any step fails, free allocated resources and return NULL.
** - Store args and tokens inside the new command.
** - Call cmd_resolve_path() to classify the command.
** - Return the new populated command structure.
*/
static t_cmd	*cmd_create(t_token *start_node, t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*arg_tokens;

	cmd = create_new_cmd();
	if (!cmd)
		return (NULL);
	arg_tokens = cmd_extract_tokens(start_node);
	if (!arg_tokens)
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->args = prepare_cmd_args(arg_tokens, shell);
	if (!cmd->args)
	{
		clear_token_list(&arg_tokens);
		free_cmd(cmd);
		return (NULL);
	}
	cmd->tokens = arg_tokens;
	cmd_resolve_path(cmd, shell);
	return (cmd);
}

/*
** parse_next_cmd
**
** This function processes one command in a pipeline.
** - Create and populate a new command from curr_token.
** - Add it to the command list (head or next of last_cmd).
** - Advance curr_token until a pipe is reached or list ends.
** - Skip the pipe token if present and continue.
** - Return the new command.
*/
static t_cmd	*parse_next_cmd(t_token **curr_token, t_shell *shell,
								t_cmd **cmds_head, t_cmd **last_cmd)
{
	t_cmd	*cmd;

	cmd = cmd_create(*curr_token, shell);
	if (!cmd)
		return (NULL);
	if (!*cmds_head)
		*cmds_head = cmd;
	else
		(*last_cmd)->next = cmd;
	*last_cmd = cmd;
	while (*curr_token && (*curr_token)->type != TK_PIPE)
		*curr_token = (*curr_token)->next;
	if (*curr_token)
		*curr_token = (*curr_token)->next;
	return (cmd);
}

/*
** parser_build_cmd_list
**
** This function converts a token list into a linked list
** of commands (t_cmd).
** - Initialize head and last_cmd pointers to NULL.
** - While tokens remain:
**     * Call parse_next_cmd() to create a command.
**     * If creation fails, reset_loop_state() and return NULL.
** - Return the head of the created command list.
*/
t_cmd	*parser_build_cmd_list(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds_head;
	t_cmd	*last_cmd;
	t_token	*curr_token;

	cmds_head = NULL;
	last_cmd = NULL;
	curr_token = tokens;
	while (curr_token)
	{
		if (!parse_next_cmd(&curr_token, shell,
				&cmds_head, &last_cmd))
			return (reset_loop_state(shell), NULL);
	}
	return (cmds_head);
}
