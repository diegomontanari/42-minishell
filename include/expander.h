/* ************************************************************************** */
/*                                                                            */
/*   expander.h                                                               */
/*                                                                            */
/*   Variable expansion: replaces $VAR and $? in command arguments.           */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

void	expand_args(t_cmd *cmd, t_shell *shell);
char	*expand_str(char *str, t_shell *shell);
char	*exp_append_char(char *str, char c);
char	*exp_append_var(char *res, char *str, int *i, t_shell *shell);

#endif
