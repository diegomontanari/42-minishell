/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:57:52 by pscarcin          #+#    #+#             */
/*   Updated: 2026/02/08 19:59:47 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*joined;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}

char	*read_and_join(int fd, char *buffer)
{
	char	*read_buf;
	ssize_t	bytes_read;
	char	*tmp;

	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buf), free(buffer), NULL);
		read_buf[bytes_read] = '\0';
		tmp = ft_strjoin_gnl(buffer, read_buf);
		free(buffer);
		buffer = tmp;
	}
	return (free(read_buf), buffer);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*remainder;
	size_t	i;

	i = 0;
	if (!*buffer || !**buffer)
		return (free(*buffer), *buffer = NULL, NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer, i + 2);
	remainder = ft_strdup(*buffer + i + ((*buffer)[i] == '\n'));
	free(*buffer);
	*buffer = remainder;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = read_and_join(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(&buffers[fd]);
	return (line);
}
