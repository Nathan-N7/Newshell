/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:13:06 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 17:48:09 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_comma(char *rline, char comma_type)
{
	size_t	i;
	int		close_comma;
	char	*phrase;

	close_comma = FALSE;
	i = 1;
	while (rline[i] != comma_type && rline[i])
		i++;
	if (rline[i] == comma_type)
		close_comma = TRUE;
	if (close_comma == TRUE)
	{
		phrase = ft_substr(rline, 0, i + 1);
		return (phrase);
	}
	else
		return (NULL);
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
		(*token)->token_word = handle_comma(rline, '\'');
	else if (rline[i] == '\"')
		(*token)->token_word = handle_comma(rline, '\"');
	else
		(*token)->token_word = handle_word(rline);
	set_token_type(token);
}
void	set_token_type(t_token **token)
{
	if (ft_strncmp((*token)->token_word, "|", 2) == TRUE)
		(*token)->token_type = PIPE;
	else if (ft_strncmp((*token)->token_word, ">>", 3) == TRUE)
		(*token)->token_type = APPEND;
	else if (ft_strncmp((*token)->token_word, "<<", 3) == TRUE)
		(*token)->token_type = HEREDOC;
	else if (ft_strncmp((*token)->token_word, ">", 2) == TRUE)
		(*token)->token_type = REDOUT;
	else if (ft_strncmp((*token)->token_word, "<", 2) == TRUE)
		(*token)->token_type = REDIN;
	else if (ft_strncmp((*token)->token_word, "\'", 2) == TRUE)
		(*token)->token_type = SINGLE_COMMA;
	else if (ft_strncmp((*token)->token_word, "\"", 2) == TRUE)
		(*token)->token_type = DOUBLE_COMMA;
	else if ((*token)->token_word == NULL)
		(*token)->token_type = OPEN_COMMA;
	else
		(*token)->token_type = WORD;
}

t_token	*create_token(char *rline)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	identify_token(&new_token, rline);
	new_token->next_token = NULL;
	return (new_token);
}
