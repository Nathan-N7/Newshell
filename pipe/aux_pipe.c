/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/05/20 16:23:58 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

int	builtin_father(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return 0;
	if (ft_strcmp(cmd->args[0], "exit") == 0
		||	ft_strcmp(cmd->args[0], "cd") == 0
		||	ft_strcmp(cmd->args[0], "unset") == 0
		||	ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	return (0);
}

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "pwd") == 0
		|| ft_strcmp(cmd->args[0], "env") == 0
		|| ft_strcmp(cmd->args[0], "echo") == 0)
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
		return (ft_pwd());
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
		return (1);
}

void	error_pipe(char *join, t_op	op)
{
	if (op == exec)
	{
		perror("execve");
		free(join);
		exit (1);
	}
	else if (op == pid)
	{
		perror("fork");
		exit(1);
	}
}