/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:55:52 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/15 14:04:29 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirects(t_data *data)
{
	t_token	*temp_t;

	temp_t = data->tokens;
	data->redirect_error = FALSE;
	while (temp_t->next && data->redirect_error == FALSE)
	{
		if (temp_t->next->token_type == REDOUT)
			handle_redout(&temp_t, data);
		else if (temp_t->next->token_type == APPEND)
			handle_append(&temp_t, data);
		else if (temp_t->next->token_type == REDIN)
			handle_redin(&temp_t, data);
		else if (temp_t->next->token_type == HEREDOC)
			handle_heredoc(&temp_t, data);
		else
			temp_t = temp_t->next;
	}
}
