/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:04:47 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/18 05:12:21 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_env_node(char *envp)
{
	t_env	*new_node;
	size_t	i;

	i = 0;
	new_node = (t_env *)malloc(sizeof(t_env) * 1);
	if (!new_node)
		return (NULL);
	while (envp[i] != '=')
		i++;
	new_node->env_name = ft_substr(envp, 0, i);
	new_node->env_value = ft_substr(envp, i + 1, ft_strlen(envp));
	new_node->next = NULL;
	return (new_node);
}

void	add_next_env(t_env **env_head, t_env *new_env)
{
	t_env	*temp_head;

	temp_head = *env_head;
	if (new_env == NULL)
		return ;
	if ((*env_head) == NULL)
	{
		(*env_head) = new_env;
		return ;
	}
	while (temp_head->next != NULL)
		temp_head = temp_head->next;
	temp_head->next = new_env;
}

void	destroy_env(t_env **env_head)
{
	t_env	*temp_next;

	while (*env_head)
	{
		temp_next = (*env_head)->next;
		free((*env_head)->env_name);
		free((*env_head)->env_value);
		free(*env_head);
		(*env_head) = temp_next;
	}
}

t_env	*env_generator(char **envp)
{
	t_env	*my_env;
	int		i;

	i = 0;
	my_env = NULL;
	while (envp[i])
	{
		add_next_env(&my_env, new_env_node(envp[i]));
		i++;
	}
	return (my_env);
}
