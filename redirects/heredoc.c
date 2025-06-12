/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:00:24 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 16:00:24 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	free_redirect(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->filename != NULL)
	{
		free(redir->filename);
		redir->filename = NULL;
	}
}

void	handle_heredoc_son(t_redirect *redir, t_envp *env, int write_fd,
		t_command *cmd)
{
	char	*rline;
	char	*e_rline;

	while (1)
	{
		rline = readline(">");
		if (g_signal || !rline || !ft_strcmp(rline, redir->filename))
		{
			if (rline)
				free(rline);
			break ;
		}
		e_rline = expand_var(rline, env);
		my_printf_fd("%s\n", write_fd, e_rline);
		free(rline);
		free(e_rline);
	}
	free_redirect(redir);
	free_env(env->envp);
	free_commands(cmd);
	close(write_fd);
	if (g_signal)
		exit(g_signal);
	else
		exit(0);
}

int	handle_heredoc(t_redirect *redir, t_envp *env, t_command *cmd)
{
	int	pid;
	int	pipefd[2];
	int	status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		close(pipefd[0]);
		handle_heredoc_son(redir, env, pipefd[1], cmd);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		env->last_stats = WTERMSIG(status) + 128;
		close(pipefd[0]);
	}
	else if (WIFEXITED(status))
		env->last_stats = WEXITSTATUS(status);
	redir->fd = pipefd[0];
	return (0);
}
