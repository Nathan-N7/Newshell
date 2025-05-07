/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:02 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 22:10:51 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_fd_list	*new_fd_node(int fd)
{
	t_fd_list	*fd_node;

	fd_node = (t_fd_list *)malloc(sizeof(t_fd_list) * 1);
	if (!fd_node)
		return (NULL);
	fd_node->fd = fd;
	fd_node->next = NULL;
	return (fd_node);
}

void	add_fd_back(t_fd_list **fd_list, t_fd_list *new_fd)
{
	t_fd_list	*temp_fd;

	if (*fd_list == NULL)
		*fd_list = new_fd;
	else
	{
		my_printf("Entra no add_fd_back\n");
		temp_fd = *fd_list;
		while (temp_fd->next != NULL)
			temp_fd = temp_fd->next;
		temp_fd->next = new_fd;
	}
}