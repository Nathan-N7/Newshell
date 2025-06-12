/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:40:16 by natrodri          #+#    #+#             */
/*   Updated: 2025/06/12 15:52:13 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"
#include "../libs/structs.h"
#include "../my_lib/libft.h"

int			g_signal = 0;

static int	trat_input(t_envp *env, char *input)
{
	if (g_signal == 130)
	{
		env->last_stats = g_signal;
		g_signal = 0;
	}
	if (!input)
		ft_exit(NULL, env);
	if (*input)
		add_history(input);
	return (0);
}

static void	trat_root(t_command *root, t_envp *env)
{
	int	resul;

	set_sig_exec();
	resul = my_pipe(root, env);
	if (resul != 0)
		env->last_stats = resul;
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
		if (trat_input(&env, input))
			break ;
		root = parsing(input, &env);
		if (root)
			trat_root(root, &env);
		free(input);
	}
	free_env(env.envp);
	rl_clear_history();
	return (0);
}
