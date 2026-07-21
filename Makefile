# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror \
          -Iinclude -Ilibft

# macOS (e.g. local dev machine) ships an old libedit as readline.h,
# which is missing symbols like rl_replace_line. On Linux (42 campus)
# the system readline is fine, so this only kicks in on Darwin.
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)
	ifneq ($(READLINE_PREFIX),)
		CFLAGS  += -I$(READLINE_PREFIX)/include
		LDFLAGS += -L$(READLINE_PREFIX)/lib
	endif
endif

# Directories
SRC_DIR   = src
OBJ_DIR   = obj
LIBFT_DIR = libft

# Executable name
NAME    = minishell

# Source files (relative to $(SRC_DIR))
SRC     = \
        error/error.c \
        cleanup/clean_env_shell.c \
        cleanup/clean_structs.c \
        cleanup/clean_utils.c \
        tokenizer/utils/quotes_utils.c \
        tokenizer/utils/input_utils.c \
        tokenizer/tokenizer_core.c \
        tokenizer/token_list.c \
        tokenizer/handlers/handle_redirection.c \
        tokenizer/handlers/handle_quotes.c \
        tokenizer/handlers/handle_words.c \
        executor/executor.c \
        executor/executor_utils.c \
        executor/executor_setup.c \
        executor/executor_cmd_utils.c \
        executor/executor_ext.c \
        executor/signals.c \
        executor/signal_utils.c \
        executor/path.c \
        executor/path_utils.c \
        executor/path_split.c \
        executor/builtins/builtins.c \
        executor/builtins/cd.c \
        executor/builtins/echo.c \
        executor/builtins/env.c \
        executor/builtins/env_utils.c \
        executor/builtins/env_node.c \
        executor/builtins/env_access.c \
        executor/builtins/exit.c \
        executor/builtins/exit_utils.c \
        executor/builtins/export.c \
        executor/builtins/export_utils.c \
        executor/builtins/export_sort.c \
        executor/builtins/export_print.c \
        executor/builtins/pwd.c \
        executor/builtins/unset.c \
        executor/pipe/pipe_exec.c \
        executor/pipe/pipe_utils.c \
        executor/pipe/pipe_child.c \
        executor/pipe/pipe_cmd.c \
        executor/pipe/pipe_io.c \
        executor/redir/redir_exec.c \
        executor/redir/redir_utils.c \
        executor/redir/redir_files.c \
        executor/redir/redir_apply.c \
        executor/redir/redir_handle.c \
        executor/redir/heredoc.c \
        parser/utils/token_utils.c \
        parser/utils/utils.c \
        parser/redirection/validate_redir.c \
        parser/redirection/cmd_args.c \
        parser/cmd_list.c \
        parser/expansion/expand_env.c \
        parser/expansion/expand_vars.c \
        shell/main.c \
        shell/prompt.c \
        shell/input.c 

# Object files
OBJ     = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Path to libft
LIBFT   = $(LIBFT_DIR)/libft.a

# Default target
all: $(NAME)

# Link final binary
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME)

# Compile objects (keeps directory structure in obj/)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Cleaning rules
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
