/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:33:34 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/14 14:09:31 by lbarreto         ###   ########.fr       */
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
}