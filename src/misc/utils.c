/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:23:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/18 04:48:54 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_metacharacter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\t' || c == 0 \
	|| c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	handle_error(int error_value, t_token *token)
{
	if (error_value == UNCLOSED_QUOTES)
		ft_putstr_fd("minishell: syntax error near unclosed quotes\n", 2);
	if (error_value == UNEXPECTED_TOKEN && token->next != NULL)
		my_printf_fd("minishell: syntax error near unexpected \
token `%s'\n", 2, token->next->token_word);
	if (error_value == UNEXPECTED_TOKEN && token->next == NULL)
		my_printf_fd("minishell: syntax error near unexpected token \
`newline'\n", 2);
}
