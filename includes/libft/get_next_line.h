/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:14:32 by lbarreto          #+#    #+#             */
/*   Updated: 2024/12/12 19:45:24 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*gnl_strdup(char *str);
int		gnl_strlen(char *str);
int		linelen(char *line);
char	*line_cut(char *line);
char	*next_line(char	*line);
char	*get_next_line(int fd);

#endif
