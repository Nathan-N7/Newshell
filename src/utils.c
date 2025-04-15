/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:23:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/14 20:08:04 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_metacharacter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\t' || c == 0 \
	|| c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	handle_error(int error_value)
{
	if (error_value == -1)
		ft_putstr_fd("Error:\nUnclosed Quotes.", 2);
	
}
