/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:25:16 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:39:15 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	heredoc_count(t_command *cmd)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < cmd->redirect_count)
	{
		if (cmd->redirects[i].type == HEREDOC)
			count++;
	}
	return (count);
}

int	process_heredoc(t_command *cmd, t_envp *env)
{
	t_redirect	*r;
	int			i;
	int			hd_count;

	hd_count = 0;
	while (cmd)
	{
		i = -1;
		while (++i < cmd->redirect_count)
		{
			r = &cmd->redirects[i];
			if (r->type == HEREDOC)
			{
				hd_count++;
				if (handle_heredoc(r, env, cmd) < 0)
					return (-1);
				if (hd_count != heredoc_count(cmd))
					close(r->fd);
				else if (env->last_stats == 130)
					return (-2);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}

int	trat_result(t_command *cmd, t_envp *env)
{
	int	resul;

	resul = process_heredoc(cmd, env);
	if (resul == -1)
	{
		env->last_stats = 1;
		return (env->last_stats);
	}
	if (resul == -2)
		g_signal = 130;
	return (0);
}
