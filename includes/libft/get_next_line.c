/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:31:14 by lbarreto          #+#    #+#             */
/*   Updated: 2024/12/12 19:43:07 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_all(char *freed)
{
	if (freed)
	{
		free(freed);
		freed = NULL;
	}
}

static int	findline(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		s1_len;
	char	*join;

	i = 0;
	j = 0;
	s1_len = gnl_strlen(s1);
	join = (char *)malloc((s1_len + gnl_strlen(s2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (i < s1_len)
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free(s1);
	free(s2);
	return (join);
}

static char	*get_line(int fd, char *line)
{
	int		bytes_read;
	char	*buffer;
	int		verify_line;

	verify_line = findline(line);
	while (verify_line == 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free_all(buffer);
			if (bytes_read < 0)
				free_all(line);
			break ;
		}
		buffer[bytes_read] = '\0';
		line = gnl_strjoin(line, buffer);
		buffer = NULL;
		verify_line = findline(line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*returned_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	else
		line = get_line(fd, line);
	while (line)
	{
		if (line[0] == '\0')
		{
			free(line);
			line = NULL;
			break ;
		}
		returned_line = line_cut(line);
		line = next_line(line);
		return (returned_line);
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		i = 0;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	while (i < 4)
	{
		if (i % 2 == 0)
			line = get_next_line(fd1);
		else
			line = get_next_line(fd2);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
}
*/
