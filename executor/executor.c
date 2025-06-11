/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/06 15:54:45 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"


static void	exec_direct_path(t_command *cmd, t_envp *env)
{
	if (access(cmd->args[0], F_OK) != 0)
	{
		my_printf_fd("%s: No such file or directory\n", 2, cmd->args[0]);
		free_commands(cmd);
		free_env(env->envp);
		exit(127);
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		my_printf_fd("%s: Permission denied\n", 2, cmd->args[0]);
		free_commands(cmd);
		free_env(env->envp);
		exit(126);
	}
	execve(cmd->args[0], cmd->args, env->envp);
	my_printf_fd("%s: execve failed\n", 2, cmd->args[0]);
	free_commands(cmd);
	free_env(env->envp);
	exit(126);
}

static void try_exec(char *join, char **path, t_command *cmd, t_envp *env)
{
    execve(join, cmd->args, env->envp);
    my_printf_fd("%s: command not found\n", 2, cmd->args[0]);
    ft_free_split(path);
    free(join);
    free_commands(cmd);
    free_env(env->envp);
    exit(127);
}

static void	exec_from_path(t_command *cmd, t_envp *env)
{
	char	*expand;
	char	**path;
	char	*join;
	char	*tmp;
	int		i;

	expand = expand_var("$PATH", env);
	if (!expand)
		expand = ft_strdup("");
	path = ft_split(expand, ':');
	free(expand);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		join = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (access(join, F_OK | X_OK) == 0)
            try_exec(join, path, cmd, env);
		free(join);
		i++;
	}
	ft_free_split(path);
}

void	execute_cmd(t_command *cmd, t_envp *env)
{
	if (ft_strchr(cmd->args[0], '/'))
		exec_direct_path(cmd, env);
	exec_from_path(cmd, env);
	my_printf_fd("%s: command not found\n", 2, cmd->args[0]);
	free_commands(cmd);
	free_env(env->envp);
	exit (127);
}
