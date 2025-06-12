/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/12 15:41:29 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:41:29 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	ft_env(t_envp *env)
{
	int	i;

	i = 0;
	if (!env || !env->envp)
		return (1);
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}
