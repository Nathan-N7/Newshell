/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:37 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 16:03:37 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	handle_redirects(t_command *cmd, t_envp *env)
{
	int			i;
	t_redirect	*r;
	int			error_flag;

	i = -1;
	error_flag = FALSE;
	while (++i < cmd->redirect_count && error_flag != TRUE)
	{
		r = &cmd->redirects[i];
		if (r->type == REDIR_OUT)
			handle_redout(r, &error_flag, env->envp);
		else if (r->type == APPEND)
			handle_append(r, &error_flag, env->envp);
		else if (r->type == REDIR_IN)
			handle_redin(r, &error_flag, env->envp);
		else if (r->type == HEREDOC)
		{
			dup2(r->fd, STDIN_FILENO);
			close(r->fd);
		}
	}
	if (error_flag == TRUE)
		return (-1);
	return (0);
}
