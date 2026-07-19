#include "minishell.h"

/*
** build_prompt
**
** Costruisce il prompt 
** Esempio: "minishell:/home/user$ "
*/
/*
static char	*build_prompt(t_shell *shell)
{
	char	*dir;
	char	*tmp;
	char	*prompt;

	(void)shell;
	dir = get_current_directory();
	if (!dir)
		return (ft_strdup("minishell$ "));
	tmp = ft_strjoin("minishell:", dir);
	free(dir);
	if (!tmp)
		return (ft_strdup("minishell$ "));
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (prompt);
}
*/
/*
** signal_prompt_handler
**
** This signal handler manages interactive prompt behavior
** (e.g., when Ctrl+C is pressed).
** - Ignore the signal value with (void)sig.
** - Print a newline to move to the next line.
** - Tell readline that a new line has started.
** - Clear the current input line with rl_replace_line().
** - Redisplay the prompt using rl_redisplay().
*/
void	signal_prompt_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static char	*build_prompt(t_shell *shell)
{
	(void)shell;
	return (ft_strdup("minishell $ "));
}

/*
** run_prompt_once
**
** Mostra il prompt, chiama readline() e gestisce l'input.
*/
static int	run_prompt_once(t_shell *shell)
{
	char	*input;
	char	*prompt;

	prompt = build_prompt(shell);
	if (!prompt)
		return (1);
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		ft_printf("exit\n");
		reset_loop_state(shell);
		return (1);
	}
	if (*input)
		add_history(input);
	process_input_line(input, shell);
	free(input);
	reset_loop_state(shell);
	return (0);
}

/*
** start_shell_loop
**
** Loop principale del minishell.
*/
int	start_shell_loop(t_shell *shell)
{
	setup_signals_interactive();
	while (1)
	{
		if (run_prompt_once(shell))
			break ;
	}
	return (shell->exit_status);
}
