/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:13:06 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/16 17:12:40 by lbarreto         ###   ########.fr       */
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
