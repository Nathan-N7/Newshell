/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:25:19 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/07 19:37:00 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redout(t_token **token, t_data *data)
{
	char	*pathname;

	pathname = create_pathname((*token)->next->token_word, data);
	if (access(pathname, F_OK) == 0)
		file_exists_redout(data, pathname);
	else
		new_file_redout(data, pathname);
}

void	file_exists_redout(t_data *data, char *pathname)
{
	int	fd;

	if (access(pathname, W_OK) == 0)
	{
		fd = open(pathname, O_WRONLY | O_TRUNC, 0644);
		dup2(fd, 1);
		add_fd_back(&data->fd, new_fd_node(fd));
		my_printf_fd("arquivo atual: %s\nfd atual: %d\n", 2, pathname, fd);
	}
	else
		my_printf_fd("Permission Denied: %s\n", 2, pathname);
}

void	new_file_redout(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, 1);
	perror("teste");
	add_fd_back(&data->fd, new_fd_node(fd));
}