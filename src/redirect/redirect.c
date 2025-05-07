/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:55:52 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 21:55:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirects(t_data *data)
{
	t_token	*temp_t;

	temp_t = data->tokens;
	while (temp_t)
	{
		if (temp_t->token_type == REDOUT)
			handle_redout(&temp_t, data);
		temp_t = temp_t->next;
	}
}
