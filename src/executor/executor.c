#include "minishell.h"
#include <sys/stat.h>

int	execute_command_type(char **args, t_shell *shell)
{
	char		*command_path;
	int			status;
	struct stat	path_stat;

	if (is_builtin(args[0]))
		return (handle_builtin(args, shell));
	command_path = find_command_path(args[0], shell);
	if (!command_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	status = check_command_path_access(command_path, args[0], &path_stat);
	if (status != 0)
		return (status);
	status = execute_external_command(command_path, args, shell);
	free(command_path);
	return (status);
}

static int	redirection_failure(char **args, int code, t_shell *shell)
{
	free_str_array(args);
	shell->exit_status = 1;
	if (code == -2)
		shell->exit_status = 130;
	return (shell->exit_status);
}

static int	handle_builtin_execution(char **args, t_shell *shell)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (execute_exit(args, shell));
	else
		return (handle_other_builtins(args, shell));
}

static int	prepare_and_redir(t_token *tokens, char ***args, t_shell *shell)
{
	int	redir_status;

	if (!tokens)
		return (handle_null_tokens(shell));
	if (check_for_pipes(tokens))
		return (handle_pipeline_execution(tokens, shell));
	*args = prepare_cmd_args(tokens, shell);
	if (!*args && count_valid_args(tokens) > 0)
		return (redirection_failure(NULL, -1, shell));
	redir_status = handle_redirection_with_tokens(tokens, shell);
	if (redir_status < 0)
		return (redirection_failure(*args, redir_status, shell));
	if (!*args)
	{
		restore_redirection(shell);
		shell->exit_status = 0;
		return (0);
	}
	return (-1);
}

int	execute_command(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		status;

	if (validate_redirection_syntax(tokens) == -1)
	{
		shell->exit_status = 2;
		return (2);
	}
	status = prepare_and_redir(tokens, &args, shell);
	if (status != -1)
		return (status);
	if (is_builtin(args[0]))
		status = handle_builtin_execution(args, shell);
	else
		status = execute_command_type(args, shell);
	restore_redirection(shell);
	free_str_array(args);
	shell->exit_status = status;
	return (status);
}
