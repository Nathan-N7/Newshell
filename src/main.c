/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:08:56 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/27 07:11:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rline;
	t_token *temp_token;
	t_env	*my_env;
	t_data	data;
	(void)argv;
	//(void)argc;
	//(void)envp;
	
	if (argc > 1)
		return (0);
	my_env = env_generator(envp);
	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		data.tokens = tokenizer(rline);
		data.last_exit = syntax_analyzer(&data);
		variable_expansion(&data.tokens, my_env);
		temp_token = data.tokens;
		if (data.last_exit == 0)
		{
			while (data.tokens)
			{
				my_printf("Token word: %s Token type: %d Add Flag: %d\n", data.tokens->token_word, data.tokens->token_type, data.tokens->add_flag);
				data.tokens = data.tokens->next;
			}
		}
		free(rline);
		destroy_tokens(&temp_token);
	} 
}
