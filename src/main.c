/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:08:56 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/06 22:52:51 by lbarreto         ###   ########.fr       */
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
	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		data.tokens = tokenizer(rline);
		data.last_exit = syntax_analyzer(&data);
		data.fd = NULL;
		data.stdout_fd = dup(1);
		variable_expansion(&data.tokens, data.envp);
		join_words(&data.tokens);
		handle_redirects(&data);
		temp_token = data.tokens;
		if (1)
		{
			while (data.tokens)
			{
				my_printf("Token word: %s Token type: %d Add Flag: %d\n", data.tokens->token_word, data.tokens->token_type, data.tokens->space_flag);
				if (data.fd != NULL)
					my_printf("Open FD: %d\n", data.fd->fd);
				data.tokens = data.tokens->next;
			}
		}
		close(data.fd->fd);
		dup2(data.stdout_fd, 1);
		close(data.stdout_fd);
		free(rline);
		destroy_tokens(&temp_token);
	} 
}
