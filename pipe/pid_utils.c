/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:25:24 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 16:21:49 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

void	advance_command(t_command **cmd)
{
	t_command	*temp_cmd;

	temp_cmd = (*cmd)->next;
	free_command(*cmd);
	*cmd = temp_cmd;
}

void	the_pid(t_envp *env, int *pids)
{
	int	pid;
	int	status;
	int	i;
	int	j;

	i = 0;
	j = -1;
	pid = -1;
	while (pids[j + 1] != -1)
		j++;
	while (pids[i] != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (pids[j] == pid)
		{
			if (WIFSIGNALED(status))
				env->last_stats = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				env->last_stats = WEXITSTATUS(status);
		}
		i++;
	}
}
