/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:50:49 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/14 20:37:29 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_next_token(t_token **token_head, t_token *new_token)
{
	t_token	*temp_head;

	temp_head = *token_head;
	if (new_token == NULL)
		return ;
	if ((*token_head) == NULL)
	{
		(*token_head) = new_token;
		return ;
	}
	while (temp_head->next_token != NULL)
		temp_head = temp_head->next_token;
	temp_head->next_token = new_token;
}

t_token	*create_token(char *rline)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	identify_token(&new_token, rline);
	new_token->next_token = NULL;
	if (new_token->token_word == NULL)
		handle_error(-1);
	return (new_token);
}

void	destroy_tokens(t_token **token_head)
{
	t_token	*temp_next;

	while ((*token_head) != NULL)
	{
		temp_next = (*token_head)->next_token;
		if ((*token_head)->token_type == OPEN_QUOTE || 
		(*token_head)->token_type == SINGLE_QUOTE ||
		(*token_head)->token_type == DOUBLE_QUOTE ||
		(*token_head)->token_type == WORD)
			free((*token_head)->token_word);
		free(*token_head);
		(*token_head) = temp_next;
	}
}