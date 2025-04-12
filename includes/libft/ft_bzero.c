/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:26:18 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/07 10:37:00 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
int	main(void)
{
	unsigned char	buffer[10];
	unsigned int	i;

	ft_bzero(buffer, 10);
	i = 0;
	while (i < sizeof(buffer))
	{
		printf("%d - %c\n", i+1, buffer[i]);
		i++;
	}
}
*/
