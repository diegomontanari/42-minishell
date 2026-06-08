/* ************************************************************************** */
/*                                                                            */
/*   error.c                                                                  */
/*                                                                            */
/*   Syntax error reporting and token validation.                             */
/*   Checks for common mistakes before parsing starts:                        */
/*   pipes at start/end, double pipes, redirection without filename.          */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Prints a syntax error message for an unexpected token. */
void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

/* Returns the string representation of a token for error messages. */
static char	*token_str(t_token *tok)
{
	if (!tok)
		return ("newline");
	return (tok->value);
}

/* Checks if the token list has valid syntax. Returns 0 if ok, -1 if not. */
int	check_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*tok;

	tok = tokens;
	if (tok && tok->type == TOKEN_PIPE)
	{
		syntax_error("|");
		shell->exit_status = 2;
		return (-1);
	}
	while (tok)
	{
		if (tok->type == TOKEN_PIPE && (!tok->next
				|| tok->next->type == TOKEN_PIPE))
		{
			syntax_error(token_str(tok->next));
			shell->exit_status = 2;
			return (-1);
		}
		if (is_redir(tok->type) && (!tok->next
				|| tok->next->type != TOKEN_WORD))
		{
			syntax_error(token_str(tok->next));
			shell->exit_status = 2;
			return (-1);
		}
		tok = tok->next;
	}
	return (0);
}
