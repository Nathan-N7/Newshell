/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:55:43 by natrodri          #+#    #+#             */
/*   Updated: 2025/05/27 15:48:05 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_tk_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_tk_type;

typedef enum e_op
{
	exec,
	pid,
	not_found
}	t_op;

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}	t_pid;

typedef struct s_redirect
{
	t_tk_type	type;
	char		*filename;
	int			fd;
}	t_redirect;

typedef struct s_command
{
	char				**args;
	t_redirect			*redirects;
	int					redirect_count;
	struct s_command	*next;
}	t_command;

typedef struct s_indexvar
{
	int	src;
	int	val;
	int	buff;
	int	var;
}	t_indexvar;

typedef struct s_expand
{
	char		*src;
	char		*buffer;
	char		*varname;
}	t_expand;

typedef struct s_token
{
	t_tk_type		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_envp
{
	char	**envp;
	int		last_stats;
}	t_envp;

#endif
