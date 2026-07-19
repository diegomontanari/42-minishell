/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 20:04:33 by user          #+#    #+#             */
/*   Updated: 2026/07/19 20:04:33 by user         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** process_heredoc_line
**
** This helper function processes a single line in a heredoc.
** If the delimiter was quoted (e.g. << 'EOF'), variable
** expansion must not happen inside the body, matching bash.
*/
static int	process_heredoc_line(int write_fd, char *line,
			int is_quoted, t_shell *shell)
{
	char	*expanded_line;

	if (is_quoted)
		expanded_line = ft_strdup(line);
	else
		expanded_line = expand_variables(line, shell);
	if (!expanded_line)
		return (-1);
	if (write(write_fd, expanded_line, ft_strlen(expanded_line)) == -1
		|| write(write_fd, "\n", 1) == -1)
	{
		perror("minishell: write");
		free(expanded_line);
		return (-1);
	}
	free(expanded_line);
	return (0);
}

/*
** read_heredoc_lines
**
** This function continuously reads user input until the heredoc
** delimiter is reached.
*/
static int	read_heredoc_lines(int write_fd, char *delimiter,
			int is_quoted, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(write_fd, line, is_quoted, shell) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

/*
** create_heredoc_pipe
**
** This function creates a pipe and fills it with heredoc input.
*/
int	create_heredoc_pipe(char *delimiter, int is_quoted, t_shell *shell)
{
	int	pipe_fd[2];
	int	result;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	result = read_heredoc_lines(pipe_fd[1], delimiter, is_quoted, shell);
	close(pipe_fd[1]);
	if (result == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
