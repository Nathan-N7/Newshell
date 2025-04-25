/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:51:32 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/25 20:01:59 by lbarreto         ###   ########.fr       */
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
			return (envp->env_value);
		}
		envp = envp->next;
	}
	free(variable);
	return (ft_strdup(""));
}

char	*replace_variable(char *token_word, int	variable_len, char *variable)
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
	while (token_word[i++] != '$')
		new_variable[i] = token_word[i];
	while (variable[j++])
		new_variable[i + j] = variable[j];
	while (i + j < new_variable_size)
	{
		my_printf("Entra nesse while aq\n");
		new_variable[i + j] = token_word[i + variable_len];
		i++;
	}
	new_variable[i + j] = '\0';
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
			while (ft_isalnum(token_word[i + 1]) == 1 \
			&& token_word[i + variable_len])
				variable_len++;
			variable = ft_substr(token_word, i + 1, variable_len);
			variable = replace_env(variable, envp); 
			token_word = replace_variable(token_word, variable_len, variable);
		}
		i++;
	}
	return (token_word);
}
