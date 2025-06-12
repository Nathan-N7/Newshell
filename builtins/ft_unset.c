/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:50:00 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:50:00 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	get_index(char **envp, char *key)
{
	int	i;
	int	len;

	len = 0;
	while (key[len] && key[len] != '=')
		len++;
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (i);
	return (-1);
}

char	**creat_env(char **envp, int idx)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	while (envp[++i])
		;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (i == idx)
		{
			free(envp[i]);
			continue ;
		}
		new_env[j++] = envp[i];
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**removed_var(char **envp, char *var)
{
	int		idx;
	char	**new_env;

	idx = get_index(envp, var);
	if (idx == -1)
		return (envp);
	new_env = creat_env(envp, idx);
	free(envp);
	return (new_env);
}

int	ft_unset(char **args, t_envp *env)
{
	int	i;

	i = -1;
	while (args[++i])
		env->envp = removed_var(env->envp, args[i]);
	if (!env->envp)
		return (1);
	return (0);
}
