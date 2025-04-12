/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:11:51 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 17:47:56 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define TRUE 1
# define FALSE 0

enum	e_tokens {
	WORD,
	PIPE,
	REDIN,
	REDOUT,
	APPEND,
	HEREDOC,
	SINGLE_COMMA,
	DOUBLE_COMMA,
	OPEN_COMMA
};

typedef struct s_token {
	char			*token_word;
	int				token_type;
	struct s_token	*next_token;
}	t_token;

char	*handle_comma(char *rline, char comma_type);
char	*handle_word(char *rline);
void	identify_token(t_token **token, char *rline);
int		is_metacharacter(char c);
void	set_token_type(t_token **token);
t_token	*create_token(char *rline);
void	add_next_token(t_token **token_head, t_token *new_token);
t_token *tokenizer(char *rline);

#endif