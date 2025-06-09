/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:53:03 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/27 18:53:03 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void file_exists_append(char *pathname, int *error_flag)
{
    int fd;

	if (isdirectory(pathname))
	{
		my_printf_fd("minishell: %s: Is a directory\n", 2, pathname);
		*error_flag = TRUE;
		return ;
	}
	if (access(pathname, W_OK) != 0)
	{
		my_printf_fd("minishell: %s: Permission denied\n", 2, pathname);
		*error_flag = TRUE;
		return ;
	}
	fd = open(pathname, O_WRONLY | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void new_file_append(char *pathname)
{
    int fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void handle_append(t_redirect *redir, int *error_flag, char **envp)
{
    char    *fname;
    char    *pathname;
	
    fname = redir->filename;
	pathname = create_pathname(fname, envp);
	if (!pathname)
		return;
	if (access(pathname, F_OK) == 0)
		file_exists_append(pathname, error_flag);
	else
		new_file_append(pathname);
	free(pathname);
}
