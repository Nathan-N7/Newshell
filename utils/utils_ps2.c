/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ps2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:43:57 by natrodri          #+#    #+#             */
/*   Updated: 2025/05/08 12:31:46 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"
void	count_args_redirs(t_token *tok, int *arg_count, int *redir_count)
{
	*arg_count = 0;
	*redir_count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD)
			(*arg_count)++;
		else if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == APPEND || tok->type == HEREDOC)
		{
			(*redir_count)++;
			tok = tok->next;
		}
		tok = tok->next;
	}
}

int	verify_aspas(char *r)
{
	int		i;
	char	aspas;

	i = 0;
	aspas = '\0';
	while (r[i])
	{
		if (r[i] == '\'' || r[i] == '"')
		{
			if (aspas == '\0')
				aspas = r[i];
			else if (aspas == r[i])
				aspas = '\0';
		}
		i++;
	}
	if (aspas == '\0')
		return (1);
	else
		return (0);
}

char	*get_value(char *name, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	result[4096];

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
		{
			j = len;
			len = 0;
			while (envp[i][j])
				result[len++] = envp[i][++j];
			result[len] = '\0';
			return (ft_strdup(result));
		}
		i++;
	}
	return (ft_strdup(""));
}

void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	if (!cmd)
		return ;
	while (cmd)
	{
		i = -1;
		tmp = cmd->next;
		if (cmd->args)
		{
			while (cmd->args[++i])
				free(cmd->args[i]);
			free(cmd->args);
		}
		i = -1;
		while (++i < cmd->redirect_count)
			free(cmd->redirects[i].filename);
		free(cmd->redirects);
		free(cmd);
		cmd = tmp;
	}
}
