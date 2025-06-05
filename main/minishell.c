/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:40:16 by natrodri          #+#    #+#             */
/*   Updated: 2025/05/27 16:27:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../my_lib/libft.h"
#include "../libs/structs.h"

void	handle_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


void	handle_sig2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}
void	set_sig(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_exec(void)
{
	signal(SIGINT, handle_sig2);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_envp		env;
	t_command	*root;

	(void)av;
	if (ac != 1)
		return (write(2, "\033[1;31m🚨 Init error \033[0m\n", 29), 0);
	env.envp = clone_env(envp);
	env.last_stats = 0;
	while (1)
	{
		set_sig();
		input = readline("\033[1;35m~sush$>\033[0m ");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		root = parsing(input, &env);
		if (root)
		{
			set_sig_exec();
			my_pipe(root, &env);
		}
		free_commands(root);
		free (input);
	}
	free_env (env.envp);
	rl_clear_history();
	return (0);
}
