/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:48:05 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 16:07:16 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

void	handle_variable(t_expand *str, t_indexvar *index, t_envp *env)
{
	char	*value;

	index->src++;
	index->var = 0;
	if (str->src[index->src] == '?')
	{
		value = ft_itoa(env->last_stats);
		while (value[index->var])
			str->buffer[index->buff++] = value[index->var++];
		free(value);
		index->src++;
		return ;
	}
	while (str->src[index->src] \
	&& (ft_isalnum(str->src[index->src]) || str->src[index->src] == '_'))
		str->varname[index->var++] = str->src[index->src++];
	str->varname[index->var] = '\0';
	value = get_value(str->varname, env->envp);
	if (!value)
		value = ft_strdup("");
	index->val = 0;
	while (value[index->val])
		str->buffer[index->buff++] = value[index->val++];
	free(value);
}

void	handle_single_quote(t_expand *str, t_indexvar *index)
{
	index->src++;
	while (str->src[index->src] && str->src[index->src] != '\'')
		str->buffer[index->buff++] = str->src[index->src++];
	if (str->src[index->src] == '\'')
		index->src++;
}

void	handle_double_quote(t_expand *str, t_indexvar *index, t_envp *env)
{
	index->src++;
	while (str->src[index->src] && str->src[index->src] != '\"')
	{
		if (str->src[index->src] == '$' \
		&& (ft_isalnum(str->src[index->src + 1]) \
		|| str->src[index->src + 1] == '_'))
			handle_variable(str, index, env);
		else
			str->buffer[index->buff++] = str->src[index->src++];
	}
	if (str->src[index->src] == '\"')
		index->src++;
}

void	process_char(t_expand *str, t_indexvar *index, t_envp *env)
{
	if (str->src[index->src] == '\'')
		handle_single_quote(str, index);
	else if (str->src[index->src] == '\"')
		handle_double_quote(str, index, env);
	else if (str->src[index->src] == '$' \
	&& (ft_isalnum(str->src[index->src + 1]) \
	|| str->src[index->src + 1] == '_' \
	|| str->src[index->src + 1] == '?'))
		handle_variable(str, index, env);
	else
		str->buffer[index->buff++] = str->src[index->src++];
}

char	*expand_var(char *src, t_envp *env)
{
	t_indexvar	index;
	char		buffer[4096];
	char		varname[256];
	t_expand	str;

	str.src = src;
	str.buffer = buffer;
	str.varname = varname;
	index.src = 0;
	index.buff = 0;
	while (src[index.src])
		process_char(&str, &index, env);
	buffer[index.buff] = '\0';
	return (ft_strdup(buffer));
}
