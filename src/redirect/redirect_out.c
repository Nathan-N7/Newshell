/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:25:19 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 22:54:58 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redout(t_token **token, t_data *data)
{
	char	*pathname;
	
	pathname = create_pathname((*token)->next->token_word, data);
	my_printf("Pathname no handle_redout: %s\n", pathname);
	if (access(pathname, F_OK) == 0)
		file_exists_redout(data, pathname);
	else
		my_printf("n achou o arquivo\n");
		//new_file_redout(data, pathname);
}

void	file_exists_redout(t_data *data, char *pathname)
{
	int	fd;


	if (access(pathname, W_OK) == 0)
	{	
		fd = open(pathname, O_WRONLY | O_TRUNC);
		//my_printf("Passa do open. Fd: %d\n", fd);
		dup2(fd, 1);
		//my_printf("New fd valor novo: %d\n", fd);
		add_fd_back(&data->fd, new_fd_node(fd));
		my_printf("N Deu segfault no fd_back\n");
	}
	else
		my_printf_fd("Permission Denied: %s\n", 2, pathname);
}