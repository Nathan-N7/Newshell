/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:01 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 16:02:01 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

static char	*get_env_value(const char *name, char **envp)
{
	size_t	len;
	int		i;

	if (!envp)
		ft_strdup("");
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

int	isdirectory(const char *pathname)
{
	struct stat	path_stat;

	if (stat(pathname, &path_stat) < 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*home_pathname(const char *filename, char **envp)
{
	char	*home;
	char	*pathname;
	char	*rest;
	size_t	total;

	home = get_env_value("HOME", envp);
	rest = ft_strdup(filename + 1);
	if (!home || !rest)
		return (free(home), free(rest), NULL);
	total = ft_strlen(home) + ft_strlen(rest) + 2;
	pathname = malloc(total);
	if (!pathname)
		return (free(home), free(rest), NULL);
	ft_strlcpy(pathname, home, total);
	ft_strlcat(pathname, rest, total);
	return (free(home), free(rest), pathname);
}

char	*relative_pathname(const char *filename, char **envp)
{
	char	*pwd;
	char	*separator;
	char	*pathname;
	size_t	total;

	pwd = get_env_value("PWD", envp);
	if (!pwd)
		return (NULL);
	separator = "/";
	total = ft_strlen(pwd) + 1 + ft_strlen(filename) + 1;
	pathname = malloc(total);
	if (!pathname)
		return (free(pwd), NULL);
	ft_strlcpy(pathname, pwd, total);
	ft_strlcat(pathname, separator, total);
	ft_strlcat(pathname, filename, total);
	free(pwd);
	return (pathname);
}

char	*create_pathname(const char *filename, char **envp)
{
	if (!filename)
		return (NULL);
	if (filename[0] == '/')
		return (ft_strdup(filename));
	else if (filename[0] == '~')
		return (home_pathname(filename, envp));
	else
		return (ft_strdup(filename));
}
