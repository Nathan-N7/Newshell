/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:55:52 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/05 20:42:08 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirects(t_data *data)
{
	t_token	*temp_t;

	temp_t = data->tokens;
	while (temp_t)
	{
		if (temp_t->token_type == REDOUT)
			handle_redout(&temp_t, data);
	}
}
char	*create_pathname(char *filename, t_data *data)
{
	char	*pwd;
	char	*separator;
	char	*pathname;

	pwd = ft_strdup("PWD");
	separator = ft_strdup("/");
	replace_env(pwd, data->envp);
	pathname = ft_strjoin(pwd, separator);
	pathname = ft_strjoin(pathname, filename);
	return (pathname);
}