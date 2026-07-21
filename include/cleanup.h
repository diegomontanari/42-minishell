#ifndef CLEANUP_H
# define CLEANUP_H

# include "tokenizer.h"
# include "executor.h"

/* Forward declaration */
struct	s_shell;

/* arrays / strings */
void	free_multiple_ptrs(char *a, char *b, char *c);
void	free_str_array(char **array);
void	free_partial_paths(char **paths, int count);
void	free_paths(char **paths);

/* token / cmd / env / shell */
void	clear_token_list(t_token **token);
void	free_env_node(t_env *node);
void	clear_env_str(t_env *env);
void	free_cmd(t_cmd *cmd);
void	clear_cmd_list(t_cmd **cmds);
void	reset_loop_state(struct s_shell *shell);
void	full_shell_cleanup(struct s_shell *shell);
void	exit_shell(t_cmd *curr, struct s_shell *shell, int exit_code);

#endif
