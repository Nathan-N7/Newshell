/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:25:19 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:41 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redout(t_token **token, t_data *data)
{
	char	*pathname;

	pathname = (*token)->next->token_word;
	if (pathname[0] == '~' || pathname [0] == '/')
		pathname = create_pathname((*token)->next->token_word, data);
	if (access(pathname, F_OK) == 0)
		file_exists_redout(data, pathname);
	else
		new_file_redout(data, pathname);
}

void	file_exists_redout(t_data *data, char *pathname)
{
	int	fd;

	if (isdirectory(pathname) == 1)
	{
		perror(pathname);
		data->last_exit = 1;
		return ;
	}
	if (access(pathname, W_OK) == 0)
	{
		fd = open(pathname, O_WRONLY | O_TRUNC);
		dup2(fd, 1);
		add_fd_back(&data->fd, new_fd_node(fd));
	}
	else
		my_printf_fd("Permission Denied: %s\n", 2, pathname);
}

void	new_file_redout(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, 1);
	add_fd_back(&data->fd, new_fd_node(fd));
}