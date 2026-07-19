#include "minishell.h"

/*
** process_tokens
**
** This function processes a list of tokens and executes a command.
** - If no tokens are provided, the function returns immediately.
** - If there is only one token and it is a word:
**     * If the word is empty, print an error and set exit code 127.
**     * If the word contains only spaces, print it as an error and
**       set exit code 127.
** - Otherwise, call execute_command to run the command and store
**   its exit status in the shell structure.
*/
static int	handle_empty_word_expansion(t_token *tokens, t_shell *shell)
{
	if (tokens->value[0] == '\0')
	{
		if (tokens->is_quoted)
		{
			ft_putstr_fd("minishell: : command not found\n", 2);
			shell->exit_status = 127;
		}
		return (1);
	}
	else if (only_spaces(tokens->value))
	{
		if (tokens->is_quoted)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tokens->value, 2);
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
		}
		return (1);
	}
	return (0);
}

void	process_tokens(t_token *tokens, t_shell *shell)
{
	int	exit_status;

	if (!tokens)
		return ;
	if (!tokens->next && tokens->type == TK_WORD)
	{
		if (handle_empty_word_expansion(tokens, shell))
			return ;
	}
	exit_status = execute_command(tokens, shell);
	shell->exit_status = exit_status;
}

/*
** process_input_line
**
** This function manages the processing of a command line input.
** - If the input is empty, the function returns immediately.
** - It first checks if a signal was received and updates the shell.
** - The input is completed (e.g., handling multi-line cases).
** - If valid, the line is added to the command history.
** - The input is then parsed into tokens and stored in the shell.
** - If parsing fails, the function stops.
** - Syntax of pipes is verified; if invalid, set exit code 2 and
**   free tokens and commands.
** - If valid, process the tokens to execute the command(s).
** - After execution, free resources related to the command.
*/
/*
				MOVED cleanup_percommand --> prompt.c

				
void	process_input_line(char *input, t_shell *shell)
{
	char	*full_line;

	if (!input || *input == '\0')
		return ;
	check_signal_received(shell);
	full_line = get_full_line(input);
	if (!full_line)
		return ;
	add_history(full_line);
	shell->tokens = parse_line_to_tokens(full_line, shell);
	if (full_line != input)
		free(full_line);
	if (!shell->tokens)
		return ;
	if (check_syntax_pipes(shell->tokens))
	{
		shell->exit_status = 2;
		reset_loop_state(shell);
		return ;
	}
	process_tokens(shell->tokens, shell);
	reset_loop_state(shell);
}*/

void	process_input_line(char *input, t_shell *shell)
{
	char	*full_line;

	if (!input || *input == '\0')
		return ;
	check_signal_received(shell);
	full_line = get_full_line(input);
	if (!full_line)
		return ;
	add_history(full_line);
	shell->tokens = parse_line_to_tokens(full_line, shell);
	if (full_line != input)
		free(full_line);
	if (!shell->tokens)
		return ;
	if (check_syntax_pipes(shell->tokens))
	{
		shell->exit_status = 2;
		return ;
	}
	process_tokens(shell->tokens, shell);
}
