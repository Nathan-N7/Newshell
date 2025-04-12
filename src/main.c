/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:08:56 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 17:51:46 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rline;

	if (argc > 1)
		return (0);
	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		printf("Passou do history\n");
		tokenizer(rline);
	}
}