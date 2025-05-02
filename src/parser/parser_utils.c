/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:13:06 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/27 06:58:51 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quote(char *rline, t_token **token, char quote_type)
{
	size_t	i;
	int		close_quote;

	close_quote = FALSE;
	i = 1;
	while (rline[i] != quote_type && rline[i])
		i++;
	if (rline[i] == quote_type)
		close_quote = TRUE;
	(*token)->token_word = ft_substr(rline, 0, i + 1);
	if (close_quote == FALSE)
		(*token)->token_type = OPEN_QUOTE;
	else if (quote_type == '\'')
		(*token)->token_type = SINGLE_QUOTE;
	else
		(*token)->token_type = DOUBLE_QUOTE;
}

char	*handle_word(char *rline)
{
	size_t	i;
	char	*word;

	i = 0;
	while (is_metacharacter(rline[i]) == 0)
		i++;
	word = ft_substr(rline, 0, i);
	return (word);
}

void	identify_token(t_token **token, char *rline)
{
	int	i;

	i = 0;
	if (rline[i] == '|')
		(*token)->token_word = "|";
	else if (rline[i] == '>' && rline[i + 1] == '>')
		(*token)->token_word = ">>";
	else if (rline[i] == '<' && rline[i + 1] == '<')
		(*token)->token_word = "<<";
	else if (rline[i] == '>')
		(*token)->token_word = ">";
	else if (rline[i] == '<')
		(*token)->token_word = "<";
	else if (rline[i] == '\'')
		handle_quote(rline, token, '\'');
	else if (rline[i] == '\"')
		handle_quote(rline, token, '\"');
	else
		(*token)->token_word = handle_word(rline);
	if (rline[i] != '\'' && rline[i] != '\"')
		set_token_type(token);
}

void	set_token_type(t_token **token)
{
	if (ft_strncmp((*token)->token_word, "|", 2) == FALSE)
		(*token)->token_type = PIPE;
	else if (ft_strncmp((*token)->token_word, ">>", 3) == FALSE)
		(*token)->token_type = APPEND;
	else if (ft_strncmp((*token)->token_word, "<<", 3) == FALSE)
		(*token)->token_type = HEREDOC;
	else if (ft_strncmp((*token)->token_word, ">", 2) == FALSE)
		(*token)->token_type = REDOUT;
	else if (ft_strncmp((*token)->token_word, "<", 2) == FALSE)
		(*token)->token_type = REDIN;
	else
		(*token)->token_type = WORD;
}

void	set_add_flag(t_token **token_head)
{
	t_token	*temp_t;

	temp_t = (*token_head);
	while (temp_t->next != NULL)
	{

		if ((temp_t->token_type == WORD \
		|| temp_t->token_type == SINGLE_QUOTE \
		|| temp_t->token_type == DOUBLE_QUOTE)
		&& (temp_t->next->token_type == WORD 
		|| temp_t->next->token_type == SINGLE_QUOTE
		|| temp_t->next->token_type == DOUBLE_QUOTE))
			temp_t->space_flag = TRUE;
		else
			temp_t->space_flag = FALSE;
		temp_t = temp_t->next;
	}
	temp_t->space_flag = FALSE;
}
