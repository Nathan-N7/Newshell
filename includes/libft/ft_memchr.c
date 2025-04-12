/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:06:28 by lbarreto          #+#    #+#             */
/*   Updated: 2024/12/09 17:57:05 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;
	unsigned int	i;

	mem = (unsigned char *)s;
	i = 0;
	if (mem == NULL)
		return (NULL);
	while (i < n)
	{
		if (mem[i] == (unsigned char)c)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{

	printf("%s", (char *)ft_memchr("012345", 's', 10));
}
*/
