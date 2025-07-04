/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:56:34 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	builtin_father(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "exit") == 0 || ft_strcmp(cmd->args[0],
			"cd") == 0 || ft_strcmp(cmd->args[0], "unset") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	return (0);
}

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "pwd") == 0 || ft_strcmp(cmd->args[0],
			"env") == 0 || ft_strcmp(cmd->args[0], "echo") == 0)
	{
		return (1);
	}
	return (0);
}

int	execute_builtin(t_envp *env, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(env));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(env));
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd->args[1], env));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		ft_exit(cmd->args, env);
		return (1);
	}
	else
		return (0);
}

void	error_pipe(char *join, t_op op)
{
	if (op == exec)
	{
		perror("execve");
		free(join);
		exit(126);
	}
	else if (op == not_found)
	{
		my_printf_fd("%s: command not found\n", 2, join);
		free(join);
		exit(127);
	}
	else if (op == pid)
	{
		perror("fork");
		exit(1);
	}
}
