/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:11:51 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 22:47:02 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <signal.h>
# include <errno.h>


# define TRUE 1
# define FALSE 0

enum	e_errors {
	UNCLOSED_QUOTES = -1,
	UNEXPECTED_TOKEN = 2,

};

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
	int				space_flag;
	struct s_token	*next;
}	t_token;

typedef	struct s_env {
	char	*env_name;
	char	*env_value;
	struct s_env	*next;
}	t_env;

typedef struct s_fd_list
{
	int					fd;
	struct s_fd_list	*next;	
} t_fd_list;


typedef struct s_data {
	t_token		*tokens;
	t_env		*envp;
	t_fd_list	*fd;
	int			stdout_fd;
	int		last_exit;
}	t_data;

void		handle_quote(char *rline, t_token **token, char quote_type);
char		*handle_word(char *rline);
void		identify_token(t_token **token, char *rline);
int			is_metacharacter(char c);
void		set_token_type(t_token **token);
t_token		*create_token(char *rline);
void		add_next_token(t_token **token_head, t_token *new_token);
t_token		*tokenizer(char *rline);
void		handle_error(int error_value, t_token *token);
void		destroy_tokens(t_token **token_head);
t_env		*new_env_node(char *envp);
t_env		*env_generator(char **envp);
void		add_next_env(t_env **env_head, t_env *new_env);
void		destroy_env(t_env **env_head);
int			pipe_analysis(t_token *token);
int			redirect_analysis(t_token *token);
int			syntax_analyzer(t_data *data);
void		variable_expansion(t_token **token_head, t_env *envp);
char		*replace_env(char *variable, t_env *envp);
char		*replace_variable(char *token_word, int	variable_len, \
char *variable);
char		*expand_variable(char *token_word, t_env *envp);
void		join_words(t_token **token_head);
void		trim_quotes(t_token **token_head);
void		join_tokens(t_token **token);
char		*create_pathname(char *filename, t_data *data);
char		*home_pathname(char *filename, t_data *data);
char		*relative_pathname(char *filename, t_data *data);
t_fd_list	*new_fd_node(int fd);
void		add_fd_back(t_fd_list **fd_list, t_fd_list *new_fd);
void		handle_redirects(t_data *data);
void		handle_redout(t_token **token, t_data *data);
void		file_exists_redout(t_data *data, char *pathname);

#endif