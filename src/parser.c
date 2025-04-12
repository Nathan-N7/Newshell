/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:36:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 20:28:08 by lbarreto         ###   ########.fr       */
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

t_token	*tokenizer(char *rline)
{
	t_token	*token_head;
	t_token	*new_token;
	size_t	i;

	i = 0;
	token_head = NULL;
	while (rline[i] != 0)
	{
		while (rline[i] == ' ' || rline[i] == '\t')
			i++;
		new_token = create_token(rline + i);
		add_next_token(&token_head, new_token);
		i += ft_strlen(new_token->token_word);
	}
	return (token_head);
}
