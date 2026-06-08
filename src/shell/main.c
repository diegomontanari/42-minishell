/* ************************************************************************** */
/*                                                                            */
/*   main.c                                                                   */
/*                                                                            */
/*   Entry point and core shell loop.                                        */
/*   init_env  : builds the env list from envp.                              */
/*   init_shell: zeroes the shell context and seeds it with the env list.    */
/*   process_line: runs one input line through tokenize → parse → execute.  */
/*   shell_loop : the main readline loop.                                    */
/*   main      : checks arguments, starts the shell, exits cleanly.         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Converts the envp array into a t_env linked list.
 * Each "KEY=value" string is split at the first '=' character.
 * Returns the head of the list. On malloc failure returns whatever
 * was built so far so the caller can free it properly.
 */
static t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*cur;
	t_env	*node;
	char	*sep;
	int		i;

	head = NULL;
	cur = NULL;
	i = -1;
	while (envp[++i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (head);
		sep = ft_strchr(envp[i], '=');
		node->key = ft_substr(envp[i], 0, sep - envp[i]);
		node->value = ft_strdup(sep + 1);
		node->next = NULL;
		if (!cur)
			head = node;
		else
			cur->next = node;
		cur = node;
	}
	return (head);
}

/*
 * Zeroes every field of the shell context and seeds it with the live
 * environment list. Backs up stdin and stdout so redirections can be
 * undone after each command. Sets interactive signal handlers so
 * ctrl-C redraws the prompt instead of killing the shell.
 */
void	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	shell->env = init_env(envp);
	signals_interactive();
}

/*
 * Runs a single input line through the three pipeline stages.
 * tokenize: splits the raw string into a linked list of typed tokens.
 * parse   : turns the token list into a t_cmd list ready for execve.
 * execute : runs the commands, handles pipes and redirections.
 * Returns early if tokenisation or parsing fails, leaving $? untouched.
 */
void	process_line(char *line, t_shell *shell)
{
	shell->tokens = tokenize(line, shell);
	if (!shell->tokens)
		return ;
	if (check_syntax(shell->tokens, shell) < 0)
		return ;
	if (parse(shell) < 0)
		return ;
	expand_args(shell->cmds, shell);
	execute(shell);
}

/*
 * Drives the read-eval-print loop until EOF (ctrl-D) or an exit builtin.
 * Empty lines are skipped silently. Non-empty lines go to history.
 * cleanup_shell frees line/tokens/cmds after each cycle so the next
 * iteration starts clean.

 * add_history is a function from the readline library.
 
 * (I moved process_line into the second if for clarity: 
 * an empty line should not be processed at all, not silently 
 * discarded inside process_line.)
 */
void	shell_loop(t_shell *shell)
{
	while (1)
	{
		shell->line = readline("minishell$ ");
		if (!shell->line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*shell->line)
		{
			add_history(shell->line);
			process_line(shell->line, shell);
		}
		cleanup_shell(shell);
	}
}

/*
 * Checks that minishell received no arguments, then runs the shell.
 * env is freed on exit; the shell struct itself lives on the stack.
 * Returns the exit status of the last executed command as the
 * process exit code, matching bash behaviour.
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell: no arguments allowed\n", 2);
		return (1);
	}
	init_shell(&shell, envp);
	shell_loop(&shell);
	free_env(shell.env);
	return (shell.exit_status);
}
