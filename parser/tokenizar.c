/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:02 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/05 20:10:05 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

t_token	*new_token(t_tk_type type, char *value)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	redir_toke(char *input, int *i, t_token **head)
{
	if (input[*i] == '>' && input[(*i) + 1] == '|')
	{
		add_token(head, new_token(REDIR_OUT, ft_strdup(">|")));
		*i += 2;
	}
	else if (input[*i] == '>' && input[(*i) + 1] == '>')
	{
		add_token(head, new_token(APPEND, ft_strdup(">>")));
		*i += 2;
	}
	else if (input[*i] == '<' && input[(*i) + 1] == '<')
	{
		add_token(head, new_token(HEREDOC, ft_strdup("<<")));
		*i += 2;
	}
	else if (input[*i] == '>')
	{
		add_token(head, new_token(REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		add_token(head, new_token(REDIR_IN, ft_strdup("<")));
		(*i)++;
	}
}

void	treat_args(char *input, int *i, t_token **head)
{
	char	buffer[4096];
	int		buf_i;
	char	q;

	buf_i = 0;
	while (input[*i] && !ft_isspace(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			q = input[*i];
			buffer[buf_i++] = input[(*i)++];
			while (input[*i] && input[*i] != q)
				buffer[buf_i++] = input[(*i)++];
			if (input[*i] == q)
				buffer[buf_i++] = input[(*i)++];
		}
		else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
			break ;
		else
			buffer[buf_i++] = input[(*i)++];
	}
	buffer[buf_i] = '\0';
	add_token(head, new_token(WORD, ft_strdup(buffer)));
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '>' || input[i] == '<')
			redir_toke(input, &i, &head);
		else if (input[i] == '|')
		{
			add_token(&head, new_token(PIPE, ft_strdup("|")));
			i++;
		}
		else
			treat_args(input, &i, &head);
	}
	return (head);
}
