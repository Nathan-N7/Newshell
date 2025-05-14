/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:25:19 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/14 13:48:45 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redout(t_token **token, t_data *data)
{
	char	*pathname;
	t_token	*temp_next;

	pathname = (*token)->next->next->token_word;
	temp_next = (*token)->next->next->next;
	if (data->last_fd_out != -2)
		close(data->last_fd_out);
	if (pathname[0] == '~' || pathname [0] == '/')
		pathname = create_pathname((*token)->next->next->token_word, data);
	if (access(pathname, F_OK) == 0)
		file_exists_redout(data, pathname);
	else
		new_file_redout(data, pathname);
	free((*token)->next->next->token_word);
	free((*token)->next->next);
	free((*token)->next);
	(*token)->next = temp_next;
}

void	file_exists_redout(t_data *data, char *pathname)
{
	int	fd;

	if (isdirectory(pathname) == 1)
	{
		my_printf_fd("minishell: %s: Is a directory\n", 2, pathname);
		data->last_exit = 1;
		return ;
	}
	if (access(pathname, W_OK) == 0)
	{
		fd = open(pathname, O_WRONLY | O_TRUNC, 0644);
		dup2(fd, 1);
		data->last_fd_out = fd;
	}
	else
	{
		my_printf_fd("minishell: %s: Permission denied\n", 2, pathname);
		data->last_exit = 1;
	}
}

void	new_file_redout(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, 1);
	data->last_fd_out = fd;
}