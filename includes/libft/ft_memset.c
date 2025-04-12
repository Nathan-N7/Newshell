/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:23:58 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/07 11:43:53 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)s;
	if (s == NULL)
		return (NULL);
	while (i < n)
	{
		b[i] = c;
		i++;
	}
	return (s);
}
/*
#include "libft.h"

int	main(void)
{
	char	buffer[10];
	unsigned int	i = 0;

	ft_memset(buffer, 'A', 10);
	while (i < 10)
	{
		printf("%d - %c\n", i, buffer[i]);
		i++;
	}
}
*/
