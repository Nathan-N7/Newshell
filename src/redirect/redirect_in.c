/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:33:34 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/22 14:08:16 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redin(t_token **token, t_data *data)
{
	char	*pathname;
	t_token	*temp_next;

	temp_next = (*token)->next->next->next;
	pathname = (*token)->next->next->token_word;
	if (pathname[0] == '~' || pathname[0] == '/')
		pathname = create_pathname((*token)->next->next->token_word, data);
	if (data->last_fd_in != -2)
		close(data->last_fd_in);
	if (access(pathname, F_OK) == 0)
		execute_redin(pathname, data);
	else
	{
		my_printf_fd("minishell: %s: No such file or directory\n", 2, pathname);
		data->last_exit = 1;
		data->redirect_error = TRUE;
	}
	free((*token)->next->next->token_word);
	free((*token)->next->next);
	free((*token)->next);
	(*token)->next = temp_next;
}

void	execute_redin(char *pathname, t_data *data)
{
	int	fd;

	if (access(pathname, R_OK) == 0)
	{
		fd = open(pathname, O_RDONLY);
		dup2(fd, 0);
		data->last_fd_in = fd;
	}
	else
	{
		my_printf_fd("minishell: %s: Permission Denied\n", 2, pathname);
		data->redirect_error = TRUE;
		data->last_exit = 1;
	}
}
