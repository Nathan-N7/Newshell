/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:08:56 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/14 20:45:34 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rline;
	t_token	*tokens;
	t_token *temp_token;
	
	(void)argv;
	(void)envp;
	
	if (argc > 1)
		return (0);
	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		tokens = tokenizer(rline);
		temp_token = tokens;
		while (tokens)
		{
			my_printf("Token word: %s Token type: %d\n", tokens->token_word, tokens->token_type);
			tokens = tokens->next_token;
		}
		free(rline);
		destroy_tokens(&temp_token);
	}
}
