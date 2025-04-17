/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:36:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/16 17:12:55 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
// int	systax_analyzer(t_data *data)
// {

// }