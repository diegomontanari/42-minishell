/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// SYSTEM INCLUDES

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>

// PROJECT INCLUDES

# include "../libft/libft.h"
# include "tokenizer.h"
# include "executor.h"
# include "parser.h"
# include "cleanup.h"

// FORWARD DECLARATION OF T_SHELL
// This allows module headers to use 'struct s_shell *' or 't_shell *'
typedef struct s_shell			t_shell;
//  CORE TYPES

// t_shell: Main shell context structure holding all runtime state.

struct s_shell
{
	char		*line;
	t_token		*tokens;
	t_cmd		*cmds;
	t_env		*env;
	int			exit_status;
	char		**args;
	char		*program_name;
	int			redirect_type;
	int			stdin_backup;
	int			stdout_backup;
};

// GLOBAL VARIABLES

extern volatile sig_atomic_t	g_signal;

// CORE FUNCTIONS 

void		init_shell_state(t_shell *shell, char **envp);
int			start_shell_loop(t_shell *shell);
void		process_input_line(char *input, t_shell *shell);
int			only_spaces(const char *str);
char		*expand_program_name(char *input, int pos, t_shell *shell);

// ERROR FUNCTIONS

void		exit_with_error(char *msg, void *context, int flag, int use_errno);
int			print_error(char *msg);
int			print_pipe_error(void);

#endif
