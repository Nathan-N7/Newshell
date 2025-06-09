/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 03:25:32 by lbarreto          #+#    #+#             */
/*   Updated: 2025/06/09 10:47:52 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

int	pipe_analysis(t_token *token, t_envp *env)
{
	if (token->type == PIPE && token->next == NULL)
	{
		my_printf_fd("minishell: syntax error near unexpected \
token `%s'\n", 2, token->value);
		env->last_stats = 2;
        return (-1);
	}
	if (token->type == PIPE && token->next->type == PIPE)
	{
		my_printf_fd("minishell: syntax error near unexpected \
token `%s'\n", 2, token->next->value);
		env->last_stats = 2;
        return (-1);
	}
    return (0);
}

int	redirect_analysis(t_token *token, t_envp *env)
{
	if ((token->type == REDIR_IN || token->type == REDIR_OUT \
	|| token->type == APPEND || token->type == HEREDOC) \
	&& (token->next == NULL))
	{
		my_printf_fd("minishell: syntax error near unexpected \
token `%s'\n", 2, token->value);
		env->last_stats = 2;
        return (-1);
	}
	if ((token->type == REDIR_IN || token->type == REDIR_OUT \
	|| token->type == APPEND || token->type == HEREDOC) \
	&& (token->next->type != WORD))
	{
		my_printf_fd("minishell: syntax error near unexpected \
token `%s'\n", 2, token->next->value);
		env->last_stats = 2;
        return (-1);
	}
    return (0);
}
int	syntax_analyzer(t_token *token, t_envp *env)
{
	if (token->type == PIPE)
	{
		my_printf_fd("minishell: syntax error near unexpected token \
`|'\n", 2);
		env->last_stats = 2;
        return (-1);
	}
	while (token)
	{
		if (redirect_analysis(token, env) == -1)
            return (-1);
		if (pipe_analysis(token, env) == -1)
            return (-1);
		token = token->next;
	}
    return (0);
}
