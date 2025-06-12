/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        	+:+   */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+      	+#+       */
/*                                                +#+#+#+#+#+  	+#+           */
/*   Created: 2025/05/27 15:38:32 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/27 15:38:32 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

void	execute_redin(char *pathname, int *error_flag)
{
	int	fd;

	if (access(pathname, F_OK) == 0)
	{
		if (access(pathname, R_OK) == 0)
			fd = open(pathname, O_RDONLY);
		else
		{
			my_printf_fd("minishell: %s: Permission Denied\n", 2, pathname);
			*error_flag = TRUE;
			return ;
		}
	}
	else
	{
		my_printf_fd("minishell: %s: No such file or directory\n", 2,
			pathname);
		*error_flag = TRUE;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redin(t_redirect *redir, int *error_flag, char **envp)
{
	char	*fname;
	char	*pathname;

	fname = redir->filename;
	pathname = create_pathname(fname, envp);
	if (!pathname)
		return ;
	execute_redin(pathname, error_flag);
	free(pathname);
}
