/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:08:56 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 20:32:38 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rline;
	t_token	*tokens;
	
	if (argc > 1)
		return (0);
	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		tokens = tokenizer(rline);
		while (tokens)
		{
			my_printf("Token word: %s Token type: %d\n", tokens->token_word, tokens->token_type);
			tokens = tokens->next_token;
		}
	}
}
