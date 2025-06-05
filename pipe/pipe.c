/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/05/27 20:06:23 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void	execute_cmd(t_command *cmd, t_envp *env)
{
	char	*expand;
	char	**path;
	int		i;
	char	*join;
	char	*tmp;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK | X_OK) == 0)
		{
			if (execve(cmd->args[0], cmd->args, env->envp))
				error_pipe(cmd->args[0], exec);
		}
		else
			error_pipe(cmd->args[0], exec);
	}
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
		{
			if (execve(join, cmd->args, env->envp) < 0)
				error_pipe(join, exec);
		}
		free(join);
		i++;
	}
	ft_free_split(path);
	printf("%s: command not found\n", cmd->args[0]);
	exit (1);
}

void	son(int in_fd, int fd[2], t_command *cmd, t_envp *env)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->redirect_count > 0)
		if (handle_redirects(cmd, env) < 0)
			exit (1);
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd))
			execute_builtin(env, cmd);
		else
			execute_cmd(cmd, env);
	}
	free_commands(cmd);
	free_env(env->envp);
	exit (0);
}

void	father(int *in_fd, int fd[2], t_command *cmd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
	else
		if (fd[0] > 0)
			close(fd[0]);
}

void	my_pipe(t_command *cmd, t_envp *env)
{
	int		fd[2];
	int		in_fd;
	int		status;
	pid_t	pid;

	in_fd = 0;
	fd[0] = -1;
	fd[1] = -1;
	while (cmd)
	{
		if (builtin_father(cmd) && !cmd->next)
		{
			env->last_stats = execute_builtin(env, cmd);
			break ;
		}
		if (cmd->next && pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
			error_pipe(NULL, pid);
		if (pid == 0)
			son(in_fd, fd, cmd, env);
		else
			father(&in_fd, fd, cmd);
		cmd = cmd->next;
	}

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			env->last_stats = WEXITSTATUS(status);
		else
			env->last_stats = 1;
	}
}
/*[cmd1] ---stdout---> [pipe1] ---stdin---> [cmd2] ---stdout---> [pipe2] ---stdin---> [cmd3]
          	(fd[1])              (fd[0])         	 (fd[1])                fd[0])
*/
