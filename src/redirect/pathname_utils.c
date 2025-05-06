/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:45:13 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 17:05:38 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_pathname(char *filename, t_data *data)
{
	char	*pathname; 

	if (*filename == '/')
		return (filename);
	else if (*filename == '~')
		pathname = home_pathname(filename, data);
	else
		pathname = relative_pathname(filename, data);
	my_printf("Meu pathname dentro da função de criar pathname: %s", pathname);
	return (pathname);
}

char	*home_pathname(char *filename, t_data *data)
{
	char	*home;
	char	*new_filename;
	char	*pathname;

	home = ft_strdup("HOME");
	new_filename = ft_strdup(filename + 1);
	replace_env(home, data->envp);
	pathname = ft_strjoin(home, new_filename);
	return (pathname);
}

char	*relative_pathname(char *filename, t_data *data)
{
	char	*pwd;
	char	*separator;
	char	*pathname;
	char	*new_filename;

	pwd = ft_strdup("PWD");
	separator = ft_strdup("/");
	new_filename = ft_strdup(filename);
	pwd = replace_env(pwd, data->envp);
	pathname = ft_strjoin(pwd, separator);
	pathname = ft_strjoin(pathname, new_filename);
	return (pathname);
}
