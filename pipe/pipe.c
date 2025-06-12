/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:51 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/11 22:56:37 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void	add_pid(t_pid **head, int new)
{
	t_pid	*tmp;
	t_pid	*new_pid;

	new_pid = (t_pid *)ft_calloc(sizeof(t_pid), 1);
	new_pid->pid = new;
	new_pid->next = NULL;
	if (!*head)
	{
		*head = new_pid;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_pid;
}

void	delete_pid(t_pid **head)
{
	t_pid	*temp_next;

	while (*head)
	{
		temp_next = (*head)->next;
		free(*head);
		(*head) = temp_next;
	}
}

int	last_pid(t_pid *pid_list)
{
	while (pid_list->next != NULL)
		pid_list = pid_list->next;
	return (pid_list->pid);		
}

int	process_heredoc(t_command *cmd, t_envp *env)
{
	t_redirect *r;
	int			i;

	while (cmd)
	{
		i = -1;
		while (++i < cmd->redirect_count)
		{
			r = &cmd->redirects[i];
			if (r->type == HEREDOC)
			{
				if (handle_heredoc(r, env, cmd) < 0)
					return (-1);
				if (i + 1 < cmd->redirect_count)
					close(r->fd);
				else if (env->last_stats == 130)
					return (-2);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}

void	son(int in_fd, int fd[2], t_command *cmd, t_envp *env)
{
	int rtrn;

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
	if (cmd->redirect_count > 0)
		rtrn = handle_redirects(cmd, env);
	if (rtrn < 0)
	{
		free_commands(cmd);
		free_env(env->envp);
		exit (rtrn);
	}
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd))
			rtrn = execute_builtin(env, cmd);
		else
			execute_cmd(cmd, env);
	}
	free_commands(cmd);
	free_env(env->envp);
	exit (rtrn);
}

void	father(int *in_fd, int fd[2], t_command *cmd)
{
	int	i;
	t_redirect	*r;

	i = -1;
	while (++i < cmd->redirect_count)
	{
		r = &cmd->redirects[i];
		if (r->type == HEREDOC)
		{
			close(r->fd);
		}
	}
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

void	the_pid(t_envp *env, t_pid **pid_list)
{
	int		pid;
	int		status;
	t_pid	*temp_next;

	pid = -1;
	while (*pid_list)
	{
		pid = waitpid(-1, &status, 0);
		if (last_pid(*pid_list) == pid)
		{
			if (WIFSIGNALED(status))
				env->last_stats = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				env->last_stats = WEXITSTATUS(status);
		}
		temp_next = (*pid_list)->next;
		free(*pid_list);
		*pid_list = temp_next;
	}
}

int	my_pipe(t_command *cmd, t_envp *env)
{
	int		fd[2];
	int		in_fd;
	t_pid	*pid_list;
	int		result;

	in_fd = 0;
	fd[0] = -2;
	fd[1] = -2;
	pid_list = NULL;
	result = process_heredoc(cmd, env);
	if (result == -1)
	{
		env->last_stats = 1;
		return (env->last_stats);
	}
	// if (result == -2)
	// 	env->last_stats = 130;
	while (cmd)
	{
		if (builtin_father(cmd) && !cmd->next)
		{
			env->last_stats = execute_builtin(env, cmd);
			break ;
		}
		add_pid(&pid_list, handle_child_and_parent(&in_fd, fd, &cmd, env));
		cmd = cmd->next;
	}
	the_pid(env, &pid_list);
	return (0);
}
/*[cmd1] ---stdout---> [pipe1] ---stdin---> [cmd2] ---stdout---> [pipe2] ---stdin---> [cmd3]
          	(fd[1])              (fd[0])         	 (fd[1])                fd[0])
*/
