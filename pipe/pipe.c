/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 16:25:17 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	trat_exec_son(t_command *cmd, t_envp *env)
{
	int	rtrn;

	rtrn = 0;
	if (cmd->redirect_count > 0)
		rtrn = handle_redirects(cmd, env);
	if (rtrn < 0)
	{
		free_commands(cmd);
		free_env(env->envp);
		exit(rtrn);
	}
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd))
			rtrn = execute_builtin(env, cmd);
		else
			execute_cmd(cmd, env);
	}
	return (rtrn);
}

void	son(int in_fd, int fd[2], t_command *cmd, t_envp *env)
{
	int	rtrn;

	rtrn = 0;
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
	rtrn = trat_exec_son(cmd, env);
	free_commands(cmd);
	free_env(env->envp);
	exit(rtrn);
}

void	father(int *in_fd, int fd[2], t_command *cmd)
{
	int			i;
	t_redirect	*r;

	i = -1;
	while (++i < cmd->redirect_count)
	{
		r = &cmd->redirects[i];
		if (r->type == HEREDOC)
			close(r->fd);
	}
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
	else if (fd[0] > 0)
		close(fd[0]);
}

int	handle_child_and_parent(int *in_fd, int *fd, t_command **cmd, t_envp *env)
{
	pid_t	pid;

	if ((*cmd)->next && pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		error_pipe(NULL, pid);
	if (pid == 0)
		son(*in_fd, fd, *cmd, env);
	else
		father(in_fd, fd, *cmd);
	return (pid);
}

int	my_pipe(t_command *cmd, t_envp *env)
{
	int	fd[2];
	int	in_fd;
	int	pids[1024];
	int	i;

	in_fd = 0;
	fd[0] = -2;
	fd[1] = -2;
	i = -1;
	if (trat_result(cmd, env))
		return (1);
	while (cmd)
	{
		if (builtin_father(cmd) && !cmd->next)
		{
			env->last_stats = execute_builtin(env, cmd);
			advance_command(&cmd);
			break ;
		}
		pids[++i] = handle_child_and_parent(&in_fd, fd, &cmd, env);
		advance_command(&cmd);
	}
	pids[++i] = -1;
	the_pid(env, pids);
	return (0);
}
