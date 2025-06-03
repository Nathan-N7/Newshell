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
	if (*c + 1 >= MAX_ARGS -1)
		return (write(2, "\033[1;31m🚨 Error: too many arguments\033[0m\n", 39), 0);
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
	if (cmd->redirect_count > MAX_REDIRS)
		return (print_error("Error"));
	cmd->redirects[cmd->redirect_count].type = (*tok)->type;
	cmd->redirects[cmd->redirect_count].filename
		= ft_strdup((*tok)->next->value);
	cmd->redirect_count++;
	*tok = (*tok)->next;
	return (1);
}

int	handle_pipe(t_command **cmd, int *count)
{
	if (!(*cmd)->args || !(*cmd)->args[0])
	{
		my_printf_fd("bash: erro de sintaxe próximo ao token inesperado `|'\n", 2);
		return (0);
	}
	(*cmd)->args[*count] = NULL;
	*cmd = new_command(&(*cmd)->next);
	if (!*cmd)
		return (0);
	*count = 0;
	return (1);
}
