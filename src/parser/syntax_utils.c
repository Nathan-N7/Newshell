/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 03:25:32 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/18 05:11:42 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_analysis(t_token *token)
{
	if (token->token_type == PIPE && token->next->token_type == PIPE)
	{
		handle_error(UNEXPECTED_TOKEN, token);
		return (UNEXPECTED_TOKEN);
	}
	while (token->next != NULL)
		token = token->next;
	if (token->token_type == PIPE)
	{
		handle_error(UNEXPECTED_TOKEN, token);
		return (UNEXPECTED_TOKEN);
	}
	return (0);
}

int	redirect_analysis(t_token *token)
{
	if ((token->token_type == REDIN || token->token_type == REDOUT \
	|| token->token_type == APPEND || token->token_type == HEREDOC) \
	&& (token->next == NULL))
	{
		handle_error(UNEXPECTED_TOKEN, token);
		return (UNEXPECTED_TOKEN);
	}
	if ((token->token_type == REDIN || token->token_type == REDOUT \
	|| token->token_type == APPEND || token->token_type == HEREDOC) \
	&& (token->next->token_type != WORD \
	&& token->next->token_type != SINGLE_QUOTE \
	&& token->next->token_type != DOUBLE_QUOTE))
	{
		handle_error(UNEXPECTED_TOKEN, token);
		return (UNEXPECTED_TOKEN);
	}
	return (0);
}
