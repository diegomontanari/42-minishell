#include "minishell.h"

/*
** init_shell_state
**
** This function initializes the shell structure with default
** values before starting the shell.
** - Set pointers (line, tokens, cmds, env, args, program_name)
**   to NULL.
** - Set exit_status to 0.
** - Copy environment variables from the system 'environ'
**   into the shell with copy_env_entries().
** - Initialize saved_stdout and saved_stdin to -1 to indicate
**   that no descriptors are saved yet.
** - Initialize redirect_type to 0.
*/
void	init_shell_state(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env = NULL;
	shell->exit_status = 0;
	shell->env = copy_env_entries(envp);
	shell->args = NULL;
	shell->program_name = NULL;
	shell->stdout_backup = -1;
	shell->redirect_type = 0;
	shell->stdin_backup = -1;
}

/*
** main
**
** Entry point of the minishell program.
** - Declare a t_shell structure to hold shell state.
** - Initialize exit_status to 0.
** - Call init_shell_state() to set up default values and environment.
** - Store the program name as "minishell".
** - Set up signal handlers:
**     * SIGINT (Ctrl+C) -> handled by signal_prompt_handler().
**     * SIGQUIT (Ctrl+\) -> ignored.
** - Start the interactive prompt loop with start_shell_loop().
** - After exiting the loop, call full_shell_cleanup() to free
**   all resources.
** - Return 0 as the program's exit code.
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		status;

	(void)argc;
	(void)argv;
	init_shell_state(&shell, envp);
	shell.program_name = ft_strdup("minishell");
	setup_signals_interactive();
	status = start_shell_loop(&shell);
	full_shell_cleanup(&shell);
	rl_clear_history();
	return (status);
}
