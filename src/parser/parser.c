/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:36:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/24 12:50:49 by lbarreto         ###   ########.fr       */
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
		if (rline[i] == '\0')
			break;
		new_token = create_token(rline + i);
		add_next_token(&token_head, new_token);
		if (new_token->token_type == REDOUT && rline[i + 1] == '|')
			i++;
		i += ft_strlen(new_token->token_word);
	}
	return (token_head);
}

int	syntax_analyzer(t_data *data)
{
	t_token	*temp_token;

	temp_token = data->tokens;
	if (data->tokens->token_type == PIPE)
	{
		my_printf_fd("minishell: syntax error near unexpected token \
`newline'\n", 2);
		return (UNEXPECTED_TOKEN);
	}
	while (temp_token)
	{
		if (temp_token->token_type == OPEN_QUOTE)
		{
			handle_error(UNCLOSED_QUOTES, temp_token);
			return (UNCLOSED_QUOTES);
		}
		if (redirect_analysis(temp_token) != 0)
			return (UNEXPECTED_TOKEN);
		if (pipe_analysis(temp_token) != 0)
			return (UNEXPECTED_TOKEN);
		temp_token = temp_token->next;
	}
	return (0);
}

void	variable_expansion(t_token **token_head, t_env *envp)
{
	t_token *temp_t;

	temp_t = *token_head;
	while (temp_t)
	{
		if (temp_t->token_type == WORD || temp_t == DOUBLE_QUOTE)
			temp_t->token_word = expand_variable(temp_t->token_word, envp);
		temp_t = temp_t->next;
	}
}
