#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ── Forward declarations ────────────────────────────────────────────── */

typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_env	t_env;
typedef struct s_shell	t_shell;

/* ── Public executor interface ───────────────────────────────────────── */

void	execute(t_shell *shell);
int		is_builtin(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
void	execute_pipeline(t_shell *shell);

/* ── Internal executor functions ─────────────────────────────────────── */

void	exec_child(t_cmd *cmd, int prev_fd, int pfd[2],
			t_shell *shell);
void	apply_redirs(t_redir *redirs, t_shell *shell);
char	*find_path(char *cmd, t_env *env);
char	*get_env_value(char *key, t_env *env);
char	**env_to_array(t_env *env);
void	free_split(char **arr);
int		handle_heredoc(char *delim, t_shell *shell);

/* ── Builtin commands ───────────────────────────────────────────────── */

int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(t_cmd *cmd, t_shell *shell);
int		builtin_unset(t_cmd *cmd, t_shell *shell);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_cmd *cmd, t_shell *shell);

/* ── Export helpers (shared across export/unset) ────────────────────── */

int		valid_identifier(char *name);
void	export_error(char *arg);
t_env	*find_or_create(char *key, t_shell *shell);

#endif
