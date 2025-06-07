/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ps1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:44:47 by natrodri          #+#    #+#             */
/*   Updated: 2025/05/08 12:32:52 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}

int	handle_word(t_command *cmd, t_token *tok, int *c, t_envp *env)
{
	cmd->args[*c] = expand_var(tok->value, env);
	(*c)++;
	return (1);
}

int	handle_redir(t_command *cmd, t_token **tok)
{
	if (!(*tok)->next || (*tok)->next->type != WORD)
	{
		if ((*tok)->next)
			my_printf_fd("bash: erro de sintaxe próximo ao token inesperado `%s'\n", 2, (*tok)->next->value);
		else
			my_printf_fd("bash: erro de sintaxe próximo ao token inesperado `newline'\n", 2);
		return (0);
	}
	cmd->redirects[cmd->redirect_count].type = (*tok)->type;
	cmd->redirects[cmd->redirect_count].filename
		= ft_strdup((*tok)->next->value);
	cmd->redirect_count++;
	*tok = (*tok)->next;
	return (1);
}

int	handle_pipe(t_command **cmd, t_token **tok, int *count)
{
	(*cmd)->args[*count] = NULL;
	*cmd = new_command((*tok)->next, &(*cmd)->next);
	if (!*cmd)
		return (0);
	*count = 0;
	return (1);
}
