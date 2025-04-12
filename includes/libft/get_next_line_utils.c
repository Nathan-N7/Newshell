/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:08:42 by lbarreto          #+#    #+#             */
/*   Updated: 2024/12/12 19:42:49 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
} 

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	linelen(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*line_cut(char *line)
{
	int		line_end;
	char	*new_line;
	int		i;

	i = 0;
	if (line == NULL)
		return (NULL);
	line_end = linelen(line);
	new_line = (char *)malloc((line_end + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	while (i < line_end)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*next_line(char	*line)
{
	int		line_end;
	char	*next_line;

	line_end = linelen(line);
	next_line = gnl_strdup(line + line_end);
	free(line);
	return (next_line);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*test;
	char	*line;

	test = ft_strdup("test\n123");
	line = line_cut(test);
	test = next_line(test);
	printf("%s\n%s", line, test);
}
*/
