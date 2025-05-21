/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:36:33 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/20 20:48:06 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_token **token, t_data *data)
{
	char	*rline;
	int		pipefd[2];
	t_token	*temp_next;

	temp_next = (*token)->next->next->next;
	rline = NULL;
	if (data->last_fd_in != -2)
		close(data->last_fd_in);
	pipe(pipefd);
	dup2(data->stdout_fd, 1);
	while (ft_strncmp(rline, (*token)->next->next->token_word, \
	ft_strlen((*token)->next->next->token_word)) != 0)
	{
		rline = readline(">");
		rline = expand_variable(rline, data->envp);
		write(pipefd[1], rline, ft_strlen(rline));
		free(rline);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	clear_redirect_tokens(token);
	data->last_fd_in = pipefd[0];
	if (data->last_fd_out != -2)
		dup2(data->last_fd_out, 1);
	(*token)->next = temp_next;
}
