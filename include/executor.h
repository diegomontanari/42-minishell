#ifndef EXECUTOR_H
# define EXECUTOR_H

/* Removed include parser.h to avoid circular dependency */
# include "tokenizer.h"
# include <sys/stat.h>

// Forward declaration
struct					s_shell;

/*  CORE EXECUTION STRUCTS  */

typedef struct s_env	t_env;

struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
};

typedef enum e_cmd_type
{
	CMD_EXTERNAL,
	CMD_BUILTIN
}	t_cmd_type;

typedef struct s_cmd	t_cmd;

struct					s_cmd
{
	char			**args;
	char			*path;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	t_cmd_type		type;
	t_token			*tokens;
};

//    1) EXECUTOR CORE (src/executor/)

/* executor.c */
int		execute_command_type(char **args, struct s_shell *shell);
int		execute_command(t_token *tokens, struct s_shell *shell);

/* executor_cmd_utils.c */
int		setup_redirection(t_token *tokens, char **args, struct s_shell *shell);
int		check_command_path_access(char *command_path, char *arg0,
			struct stat *path_stat);

/* executor_setup.c */
int		handle_null_tokens(struct s_shell *shell);
char	**prepare_cmd_args(t_token *tokens, struct s_shell *shell);

/* executor_utils.c */

char	**build_envp_from_list(struct s_env *env);

/* executor_ext.c */
int		execute_exit(char **args, struct s_shell *shell);
int		handle_other_builtins(char **args, struct s_shell *shell);
int		execute_external_command(char *cmd_path, char **args,
			struct s_shell *shell);

/* signals.c */
void	signal_handler_interactive(int sig);
void	signal_handler_executing(int sig);
void	setup_signals_interactive(void);
void	setup_signals_executing(void);
void	setup_signals_child(void);

/* signal_utils.c */
void	setup_signal_action(int signal, void (*handler)(int), int flags);
int		handle_signal_exit_status(int status, struct s_shell *shell);
int		check_signal_received(struct s_shell *shell);
void	print_signal_message(int signal_number, int status);

/* path.c */
char	*find_command_path(char *command, struct s_shell *shell);

/* path_split.c */
char	**split_path_env(char *path_env);

/* path_utils.c */
int		count_path_segments(char *path_env);
char	**allocate_paths_array(int count);
char	*extract_path_segment(char *path_env, int start, int len);

//  2) BUILTINS (src/executor/builtins/)

/* builtins.c */
int		is_builtin(char *command);
int		handle_builtin(char **args, struct s_shell *shell);

/* cd.c */
int		handle_cd(char **args, struct s_shell *shell);
int		handle_cd_home(struct s_shell *shell);
int		handle_cd_dash(struct s_shell *shell);
int		handle_cd_path(struct s_shell *shell, char *path);
void	update_pwd_vars(struct s_shell *shell, char *old_pwd);

/* echo.c */
int		handle_echo(struct s_shell *shell, char **args);

/* env.c */
int		handle_env(struct s_shell *shell, char **args);

/* env_utils.c */
t_env	*create_env_node(char *key, char *value, int exported);
t_env	*copy_env_entries(char **env_entries);
size_t	count_env_nodes(t_env *env);
int		env_list_size(t_env *env);

/* env_node.c */
int		add_env_node(t_env **env_list, t_env *new_node);
int		update_env_node(t_env *node, char *new_value, int exported_flag);
t_env	*find_env_node(t_env *env_list, char *key);

/* env_access.c */
char	*get_env_value(t_env *env, const char *key);
int		update_env_value_if_exists(t_env *envp, const char *key,
			const char *value);
int		append_env_value_if_missing(t_env **envp, const char *key,
			const char *value);
int		set_env_value(t_env **envp, const char *key, const char *value);

/* exit.c */
int		handle_exit(struct s_shell *shell, char **args);

/* exit_utils.c */
int		skip_spaces(const char *str);
int		check_atol_conversion(char *str);
int		is_numeric(char *str);

/* export.c */
int		export_variable(t_env **env_list_ptr, char **args);
int		handle_export(t_env **env_list, char **argv);

/* export_utils.c */
int		is_valid_identifier(char *str);
char	*extract_key(char *str);
char	*extract_value(char *str);

/* export_sort.c */
void	selection_sort_env(t_env **arr, int size);
t_env	**env_list_to_array(t_env *env, int size);

/* export_print.c */
void	print_exported_recursive(t_env **arr, int size, int i);
void	print_export_sorted(t_env *env_list);

/* pwd.c */
int		handle_pwd(void);

/* unset.c */
int		handle_unset(t_env **env_list, char **argv);
int		unset_variable(t_env **env_list, char **args);
int		remove_env_node(t_env **env_list_ptr, char *key);

//   3) PIPELINE (src/executor/pipe/)

/* pipe_exec.c */
int		execute_pipeline(t_cmd *cmds, struct s_shell *shell);
int		handle_pipeline_execution(t_token *tokens, struct s_shell *shell);

/* pipe_child.c */
void	execute_child_process(t_cmd *curr, int prev_fd, int *pipe_fd,
			struct s_shell *shell);

/* pipe_utils.c */
int		check_for_pipes(t_token *tokens);
t_cmd	*create_new_cmd(void);
int		check_syntax_pipes(t_token *tokens);

/* pipe_cmd.c */
int		setup_command_execution(t_cmd *curr, int *fds, pid_t *pid);
int		execute_single_command(t_cmd *curr, int *fds,
			struct s_shell *shell, pid_t *last_pid);

/* pipe_io.c */
void	setup_child_io_and_signals(t_cmd *curr, int prev_fd, int *pipe_fd,
			struct s_shell *shell);

//   4) REDIRECTION (src/executor/redir/)

/* redir_exec.c */
int		handle_input_redirection_with_tokens(t_token *tokens,
			struct s_shell *shell);
int		handle_output_redirection_token(t_token *tokens, struct s_shell *shell);
int		handle_redirection_with_tokens(t_token *tokens, struct s_shell *shell);

/* redir_files.c */
int		open_input_file(t_token *curr, struct s_shell *shell);
int		open_output_file(t_token *curr, char **filename);
int		handle_new_output_fd(int new_fd, int *file_fd, struct s_shell *shell,
			t_token *curr);

/* redir_apply.c */
void	restore_input_redirection(struct s_shell *shell);
void	update_input_fd(int *input_fd, int new_input_fd);
int		setup_output_redirection(int file_fd, struct s_shell *shell);

/* redir_utils.c */
int		open_regular_file(char *filename, int token_type);
int		open_file_by_type(char *filename, int token_type,
			int is_quoted, struct s_shell *shell);
int		has_input_redirection(t_token *tokens);
int		has_output_redirection(t_token *tokens);

/* redir_handle.c */
void	restore_redirection(struct s_shell *shell);
int		apply_input_redirection(int input_fd, struct s_shell *shell);
int		handle_single_input_redirect(t_token *curr, struct s_shell *shell,
			int *input_fd);
void	setup_sigpipe_handling(void);

/* heredoc.c */
int		create_heredoc_pipe(char *delimiter, int is_quoted,
			struct s_shell *shell);

#endif
