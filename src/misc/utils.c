/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:23:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/20 20:51:05 by lbarreto         ###   ########.fr       */
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

void	free_split(char **split_str)
{
	int	i;

	i = 0;
	while (split_str[i])
	{
		if (split_str[i] != NULL)
		{
			split_str[i] = NULL;
			free(split_str[i]);
		}
		i++;
	}
	free(split_str);
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
