/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:21:23 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/22 14:11:30 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*take_cmd_name(t_data *data)
{
	char	*cmd_name;

	cmd_name = ft_strdup(data->tokens->token_word);
	return (cmd_name);
}

char	**create_cmd_args(t_data *data)
{
	char	**cmd_args;
	t_token	*temp_token;
	int		args_size;

	args_size = 0;
	temp_token = data->tokens;
	while (temp_token)
	{
		args_size++;
		temp_token = temp_token->next;
	}
	cmd_args = (char **)malloc(sizeof(char *) * (args_size + 1));
	temp_token = data->tokens;
	args_size = 0;
	while (temp_token)
	{
		cmd_args[args_size] = ft_strdup(temp_token->token_word);
		temp_token = temp_token->next;
		args_size++;
	}
	cmd_args[args_size] = NULL;
	return (cmd_args);
}

char	*find_cmd_path(t_data *data, char *cmd_name)
{
	char	*cmd_path;
	char	**paths;
	int		i;

	i = 0;
	cmd_path = ft_strdup("PATH");
	cmd_path = replace_env(cmd_path, data->envp);
	paths = ft_split(cmd_path, ':');
	free(cmd_path);
	cmd_path = ft_strdup(cmd_name);
	free(cmd_name);
	while (paths[i])
	{
		paths[i] = ft_strconcat(paths[i], "/");
		paths[i] = ft_strconcat(paths[i], cmd_path);
		if (access(paths[i], X_OK) == 0)
		{
			free(cmd_path);
			cmd_path = ft_strdup(paths[i]);
		}
		i++;
	}
	free_split(paths);
	return (cmd_path);
}

int	execute_command(t_data *data)
{
	//int		pid;
	char	*cmd;
	char	**args;

	cmd = take_cmd_name(data);
	cmd = find_cmd_path(data, cmd);
	args = create_cmd_args(data);
	if (execve(cmd, args, NULL) == -1)
		my_printf("Execve falhou!\n cmd_path: %s\nargs[0]: %s\nargs[1]: %s\n", cmd, args[0],args[1]);
	return (0);
}