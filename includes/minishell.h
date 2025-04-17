/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:11:51 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/17 17:49:43 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>

# define TRUE 1
# define FALSE 0

enum	e_tokens {
	WORD,
	PIPE,
	REDIN,
	REDOUT,
	APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	OPEN_QUOTE
};

typedef	struct s_token {
	char			*token_word;
	int				token_type;
	struct s_token	*next;
}	t_token;

typedef	struct s_env {
	char	*env_name;
	char	*env_value;
	struct s_env	*next;
}	t_env;


typedef struct s_data {
	t_token	*tokens;
	t_env	*envp;
}	t_data;

void	handle_quote(char *rline, t_token **token, char quote_type);
char	*handle_word(char *rline);
void	identify_token(t_token **token, char *rline);
int		is_metacharacter(char c);
void	set_token_type(t_token **token);
t_token	*create_token(char *rline);
void	add_next_token(t_token **token_head, t_token *new_token);
t_token	*tokenizer(char *rline);
void	handle_error(int error_value);
void	destroy_tokens(t_token **token_head);
t_env	*new_env_node(char *envp);
t_env	*env_generator(char **envp);
void	add_next_env(t_env **env_head, t_env *new_env);
void	destroy_env(t_env **env_head);

#endif