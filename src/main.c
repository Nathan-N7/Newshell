/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:08:56 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/22 15:30:17 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rline;
	t_token *temp_token;
	t_data	data;
	(void)argv;
	//(void)argc;
	//(void)envp;
	
	if (argc > 1)
		return (0);
	data.envp = env_generator(envp);
	data.stdout_fd = dup(1);
	data.stdin_fd = dup(0);
	data.last_fd_in = -2;
	data.last_fd_out = -2;
	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		data.tokens = tokenizer(rline);
		data.last_exit = syntax_analyzer(&data);
		variable_expansion(&data.tokens, data.envp);
		join_words(&data.tokens);
		if (handle_redirects(&data) != 0)
		{
			dup2(data.stdout_fd, 1);
			dup2(data.stdin_fd, 0);
			free(rline);
			//destroy_tokens(&temp_token);
			continue ;
		}
		temp_token = data.tokens;
		// while (data.tokens)
		// {
		// 	my_printf("Token word: %s Token type: %d Add Flag: %d\n", data.tokens->token_word, data.tokens->token_type, data.tokens->space_flag);
		// 	data.tokens = data.tokens->next;
		// 	my_printf("Token: %p\n", data.tokens);
		// }
		//my_printf("Ta passando do temp_token\n Token_head: %s\n",data.tokens->token_word);
		execute_command(&data);
		dup2(data.stdout_fd, 1);
		dup2(data.stdin_fd, 0);
		free(rline);
		destroy_tokens(&temp_token);
	}
} 

