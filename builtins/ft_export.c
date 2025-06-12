/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        	+:+   */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+      	+#+       */
/*                                                +#+#+#+#+#+  	+#+           */
/*   Created: 2025/06/12 15:44:30 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:44:30 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

char	**new_envp(char **envp, char *arg)
{
	int		i;
	char	**envp_new;

	i = get_index(envp, arg);
	if (i >= 0)
	{
		free(envp[i]);
		envp[i] = ft_strdup(arg);
		return (envp);
	}
	i = -1;
	while (envp[++i])
		;
	envp_new = malloc(sizeof(char *) * (i + 2));
	if (!envp_new)
		return (NULL);
	i = -1;
	while (envp[++i])
		envp_new[i] = envp[i];
	envp_new[i++] = ft_strdup(arg);
	envp_new[i] = NULL;
	free(envp);
	return (envp_new);
}

int	verify_var(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_order(t_envp *env)
{
	char	**order;
	char	*tmp;
	int		len;
	int		k;

	order = clone_env(env->envp);
	len = 0;
	while (order[len])
		len++;
	k = -1;
	while (++k + 1 < len)
	{
		if (order[k] && order[k + 1] && ft_strcmp(order[k], order[k + 1]) > 0)
		{
			tmp = order[k];
			order[k] = order[k + 1];
			order[k + 1] = tmp;
			k = -1;
		}
	}
	k = -1;
	while (order[++k] && k < len)
		printf("declare -x %s\n", order[k]);
	free_env(order);
}

int	ft_export(char **args, t_envp *env)
{
	int		i;
	int		rtrn;
	char	**tmp;

	i = -1;
	rtrn = 0;
	if (!args[1])
		return (print_order(env), 0);
	while (args[++i])
	{
		if (!verify_var(args[i]))
		{
			printf("export: `%s`: not a valid identifier\n", args[i]);
			rtrn = 1;
			continue ;
		}
		if (ft_strchr(args[i], '='))
		{
			tmp = new_envp(env->envp, args[i]);
			if (!tmp)
				return (1);
			env->envp = tmp;
		}
	}
	return (rtrn);
}
