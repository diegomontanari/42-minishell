#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "executor.h"

// Forward declaration
struct	s_shell;

//  1) PARSER ENTRY POINTS

t_cmd		*parser_build_cmd_list(t_token *token_list,
				struct s_shell *shell);

//  2) VARIABLE & ENVIRONMENT EXPANSION 

char		*expand_variables(char *input, struct s_shell *shell);
char		*expand_program_name(char *input, int pos, struct s_shell *shell);
char		*expand_exit_status(char *str, int start, struct s_shell *shell);
char		*expand_environment_variable(char *str, int start,
				int end, struct s_shell *shell);
char		*get_variable_value(char *str, int start,
				int end, struct s_shell *shell);
char		*expand_join_parts(char *before, char *value, char *after);
int			expand_find_end_index(char *str, int start);

//  3) ARGUMENT PROCESSING 

//int			populate_command_args(t_cmd *command, t_token *token_start);
char		**args_extract_from_tokens(t_token *tokens);
char		**args_fill_array(t_token *tokens, char **args,
				int word_count);
int			count_valid_args(t_token *tokens);

//  4) TOKEN PROCESSING 
// Moved to tokenizer.h
char		*extract_and_expand_word(const char *input, int *i,
				struct s_shell *shell);

//  5) REDIRECTION VALIDATION 

int			valid_syntax_token(t_token *curr);
int			is_redir_target(t_token *tokens, t_token *curr);
int			is_redirection_file(t_token *tokens, t_token *curr);

//  6) TOKEN LIST UTILITIES 
// Note: add_token_to_list and get_last_token are now in tokenizer_new.h

char		*extract_raw_word(const char *input, int *i);

#endif
