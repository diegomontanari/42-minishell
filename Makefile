# **************************************************************************** #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Homebrew readline (macOS ships libedit, not GNU readline)
RL_DIR		= $(shell brew --prefix readline 2>/dev/null)
RL_INC		= -I$(RL_DIR)/include
RL_LIB		= -L$(RL_DIR)/lib -lreadline

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# ── Source files ─────────────────────────────────────────────────────────── #

SRC			= src/shell/main.c \
			  src/shell/signals.c \
			  src/tokenizer/tokenizer.c \
			  src/tokenizer/handlers/handle_operator.c \
			  src/tokenizer/handlers/handle_word.c \
			  src/parser/parser.c \
			  src/parser/parse_redir.c \
			  src/parser/parse_args.c \
			  src/expander/expander.c \
			  src/expander/expand_args.c \
			  src/executor/executor.c \
			  src/executor/find_path.c \
			  src/executor/env_utils.c \
			  src/executor/pipe/pipeline.c \
			  src/executor/pipe/child.c \
			  src/executor/redir/redir.c \
			  src/executor/redir/heredoc.c \
			  src/executor/builtins/builtin_echo.c \
			  src/executor/builtins/builtin_cd.c \
			  src/executor/builtins/builtin_pwd.c \
			  src/executor/builtins/builtin_export.c \
			  src/executor/builtins/builtin_export_utils.c \
			  src/executor/builtins/builtin_unset.c \
			  src/executor/builtins/builtin_env.c \
			  src/executor/builtins/builtin_exit.c \
			  src/error/error.c \
			  src/cleanup/cleanup.c

OBJ			= $(SRC:.c=.o)

# ── Rules ────────────────────────────────────────────────────────────────── #

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RL_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(RL_INC) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
