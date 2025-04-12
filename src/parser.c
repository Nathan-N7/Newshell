/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:36:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 18:02:15 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_next_token(t_token **token_head, t_token *new_token)
{
	t_token	*temp_head;

	temp_head = *token_head;
	if (new_token == NULL)
		return ;
	if (*token_head == NULL)
	{
		*token_head = new_token;
		return ;
	}
	while (temp_head->next_token != NULL)
		temp_head = temp_head->next_token;
	temp_head->next_token = new_token;
}

t_token *tokenizer(char *rline)
{
	t_token	*token_head;
	t_token	*token;
	int		i;

	i = 0;
	token_head = NULL;
	token = token_head;
	while (rline[i])
	{
		while (rline[i] == ' ' || rline[i] == '\t')
			i++;
		add_next_token(&token_head, create_token(rline + i));
		//i += ft_strlen(token->token_word);
		//token = token->next_token;
	}
	return (token_head);
}