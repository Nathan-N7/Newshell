/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:41:39 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:41:41 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

void	set_path(char **envp, char *path, char *name)
{
	int		i;
	char	*tmp;
	char	*new_var;

	i = get_index(envp, name);
	if (i == -1)
		return ;
	free(envp[i]);
	tmp = ft_strjoin(name, "=");
	new_var = ft_strconcat(tmp, path);
	envp[i] = new_var;
}

int	verify_dir(char *path)
{
	if (access(path, F_OK) != 0)
	{
		my_printf_fd("minishell: cd: %s: No such file or directory\n", 2, path);
		return (1);
	}
	if (isdirectory(path) == 0)
	{
		my_printf_fd("minishell: cd: %s: Not a directory\n", 2, path);
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		my_printf_fd("minishell: cd: %s: Permission denied\n", 2, path);
		return (1);
	}
	return (0);
}

int	trat_env(char *path, t_envp *env)
{
	char	*path_old;
	char	*path_pwd;

	path_old = getcwd(NULL, 0);
	if (!path_old)
		path_old = expand_var("$PWD", env);
	if (chdir(path) != 0)
	{
		free(path_old);
		perror("cd");
		return (1);
	}
	path_pwd = getcwd(NULL, 0);
	if (path_old)
		set_path(env->envp, path_old, "OLDPWD");
	if (!path_pwd)
	{
		my_printf_fd("cd: cannot access parent directories: ", 2);
		perror("cd");
	}
	else
		set_path(env->envp, path_pwd, "PWD");
	free(path_old);
	free(path_pwd);
	return (0);
}

int	ft_cd(char *path, t_envp *env)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (!home)
		{
			my_printf_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		path = home;
	}
	if (verify_dir(path))
		return (1);
	if (trat_env(path, env))
		return (1);
	return (0);
}
