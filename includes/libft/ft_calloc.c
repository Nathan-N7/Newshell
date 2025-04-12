/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:28:39 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/14 13:48:24 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	memsize;

	memsize = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		mem = (unsigned char *)malloc(1);
		ft_bzero(mem, 1);
		return ((void *)mem);
	}
	if (memsize / nmemb != size)
		return (NULL);
	mem = (unsigned char *)malloc(memsize);
	if (!mem)
		return (NULL);
	ft_bzero(mem, memsize);
	return ((void *)mem);
}
/*
int	main(void)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = ft_calloc(50, 2);
	while (i < 100)
	{
		printf("%d", (int)ptr[i]);
		i++;
	}
}
*/
