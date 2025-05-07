/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:51:32 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 22:57:55 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_env(char *variable, t_env *envp)
{
	while (envp)
	{
		if (ft_strncmp(variable, envp->env_name, ft_strlen(variable) + 1) == 0)
		{
			free(variable);
			return (ft_strdup(envp->env_value));
		}
		envp = envp->next;
	}
	free(variable);
	return (ft_strdup(""));
}

char	*replace_variable(char *token_word, int variable_len, char *variable)
{
	int		i;
	int		j;
	int		new_variable_size;
	char	*new_variable;

	i = -1;
	j = -1;
	new_variable_size = ft_strlen(token_word) - variable_len + \
	ft_strlen(variable) + 1;
	new_variable = (char *)malloc(new_variable_size);
	if (!new_variable)
		return (NULL);
	while (token_word[++i] != '$')
		new_variable[i] = token_word[i];
	while (variable[++j])
		new_variable[i + j] = variable[j];
	while (i + j + 1 < new_variable_size)
	{
		new_variable[i + j] = token_word[i + variable_len + 1];
		i++;
	}
	new_variable[i + j - 1] = '\0';
	free(token_word);
	return (new_variable);
}

char	*expand_variable(char *token_word, t_env *envp)
{
	int		variable_len;
	int		i;
	char	*variable;

	i = 0;
	while (token_word[i])
	{
		if (token_word[i] == '$')
		{
			variable_len = 0;
			while (ft_isalnum(token_word[i + 1 + variable_len]) == 1 \
			&& token_word[i + 1 + variable_len])
				variable_len++;
			variable = ft_substr(token_word, i + 1, variable_len);
			variable = replace_env(variable, envp);
			token_word = replace_variable(token_word, variable_len, variable);
			if (ft_strncmp(variable, "", 2) == 0 \
			&& token_word[i + ft_strlen(variable)] == '\0')
				break ;
			else if (ft_strncmp(variable, "", 2) == 0)
				i--;
		}
		i++;
	}
	return (token_word);
}

void	join_words(t_token **token_head)
{
	t_token	*temp_t;

	trim_quotes(token_head);
	temp_t = *token_head;
	while (temp_t->next)
	{
		if (temp_t->next->space_flag == 0 && (temp_t->token_type == WORD \
		|| temp_t->token_type == SINGLE_QUOTE \
		|| temp_t->token_type == DOUBLE_QUOTE) \
		&& (temp_t->next->token_type == WORD \
		|| temp_t->next->token_type == SINGLE_QUOTE \
		|| temp_t->next->token_type == DOUBLE_QUOTE))
			join_tokens(&temp_t);
		else if (temp_t->next != NULL)
			temp_t = temp_t->next;
	}
	temp_t = *token_head;
	while (temp_t)
	{
		if (temp_t->token_type == SINGLE_QUOTE \
		|| temp_t->token_type == DOUBLE_QUOTE)
			temp_t->token_type = WORD;
		temp_t = temp_t->next;
	}
}

void	join_tokens(t_token **token)
{
	t_token	*temp_next;

	temp_next = (*token)->next->next;
	(*token)->token_word = ft_strjoin((*token)->token_word, \
	(*token)->next->token_word);
	free((*token)->next);
	(*token)->next = temp_next;
}
