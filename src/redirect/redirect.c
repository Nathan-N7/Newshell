/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:55:52 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/22 15:57:17 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirects(t_data *data)
{
	t_token	*temp_t;

	shuffle_tokens(&data->tokens);
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
	if (data->redirect_error == TRUE)
		return (-1);
	return (0);
}

void	shuffle_tokens(t_token **token_head)
{
	t_token	*temp_t;
	t_token	*temp_head;
	t_token	*temp_next;

	temp_t = *token_head;
	temp_head = *token_head;
	if (temp_t->token_type != WORD)
	{
		while (temp_t->token_type != WORD || temp_t->next->token_type != WORD)
			temp_t = temp_t->next;
		temp_next = temp_t->next;
		temp_t->next = temp_t->next->next;
		temp_next->next = temp_head;
		*token_head = temp_next;
	}
}
