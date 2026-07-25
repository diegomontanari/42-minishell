*This project has been created as part of the 42 curriculum by dmontana and pscarcin.*

# Minishell

## Description

**Minishell** is a small Unix shell written in C. It reproduces the core
behaviour of a command-line interpreter by reading user input, tokenizing and
parsing it, expanding variables, applying redirections, creating pipelines, and
executing built-in or external commands.

At runtime, input flows through `readline` and the tokenization stage, which
handles words, quotes, and variable expansion. The parser then validates and
organizes the tokens and builds the command structures required for pipelines
before passing execution to the executor. After each command, the shell
restores redirected file descriptors and releases the temporary structures
created for that iteration.

The project is divided into distinct modules:

- the tokenizer handles words, quotes, variable expansion, pipes, and
  redirection tokens;
- the parser validates and organizes tokens and builds the command structures
  required for pipelines;
- the executor resolves executable paths, forks child processes, connects
  pipelines, and applies file-descriptor redirections;
- the built-in module implements `echo`, `cd`, `pwd`, `export`, `unset`,
  `env`, and `exit`;
- the signal and cleanup modules manage interactive behaviour and allocated
  resources.

The implementation supports single and double quotes, `$VARIABLE` and `$?`
expansion, input and output redirections (`<`, `>`, `>>`, and `<<`), pipelines,
command history, absolute and relative executable paths, and commands resolved
through `PATH`.

## Instructions

### Requirements

- Linux environment used by the 42 campus
- `cc` compiler
- GNU Readline development library
- `make`

### Compilation

To compile the project, run:

```bash
make
```

This builds the Libft dependency and generates:

```bash
minishell
```

### Execution

Start the interactive shell with:

```bash
./minishell
```

Example commands:

```bash
echo "Hello, Minishell"
export MESSAGE=hello
echo "$MESSAGE"
cat < input.txt | grep word > output.txt
cat << EOF | wc -l
```

Use `Ctrl-C` to interrupt the current input or foreground command, `Ctrl-\` to
send `SIGQUIT` to a foreground command, and `Ctrl-D` on an empty prompt to exit.

### Cleaning

```bash
make clean
make fclean
make re
```

## Resources

- The Minishell subject and official evaluation sheet
- GNU Bash Reference Manual
- GNU Readline documentation
- POSIX and system manual pages
- `man fork`
- `man execve`
- `man waitpid`
- `man pipe`
- `man dup`
- `man dup2`
- `man open`
- `man chdir`
- `man getcwd`
- `man access`
- `man unlink`
- `man getenv`
- `man signal`
- `man kill`
- `man sigaction`
- `man perror`
- `man strerror`
- `man readline`

## AI Usage

AI tools were used by both authors as learning and review aids to compare the
implementation with the subject and evaluation sheet, audit the 42 Norm,
analyse the control flow, compare and integrate Libft implementations, design
tests, investigate edge cases and memory errors, and improve the documentation.

The project was also studied through peer learning, code review, and
discussions with other students, including comparison with an existing
reference implementation. Its architecture and behaviour were reviewed,
tested, discussed, and modified so that both authors can understand, explain,
maintain, and take responsibility for the submitted version.
