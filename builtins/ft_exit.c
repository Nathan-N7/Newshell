/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:43:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:47:18 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || *str == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	set_error(char *args, t_envp *env, t_op op)
{
	if (op == num)
	{
		my_printf_fd("minishell: exit: %s: numeric argument required\n", 2,
			args);
		env->last_stats = 2;
		free_env(env->envp);
		exit(2);
	}
	else if (op == arg)
	{
		my_printf_fd("minishell: exit: too many arguments\n", 2);
		env->last_stats = 1;
	}
}

void	ft_exit(char **args, t_envp *env)
{
	write(1, "exit\n", 5);
	if (!args)
	{
		env->last_stats = 0;
		free_env(env->envp);
		exit(0);
	}
	if (args[1])
	{
		if (!is_numeric(args[1]))
			set_error(args[1], env, num);
		else if (args[2])
		{
			set_error(args[2], env, arg);
			return ;
		}
		env->last_stats = (unsigned char)ft_atoi(args[1]);
		free_env(env->envp);
		exit(env->last_stats);
	}
	env->last_stats = 0;
	free_env(env->envp);
	exit(0);
}
