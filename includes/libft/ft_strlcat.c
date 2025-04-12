/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:49:47 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/16 12:56:34 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(dst) + ft_strlen(src);
	if (ft_strlen(dst) >= size)
		return (size + ft_strlen(src));
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i])
		i++;
	while (*src && i < size - 1)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	return (len);
}
/*
#include <bsd/string.h>
int	main (void)
{
	char	dest1[13] = "tripouille";
	char	dest2[13] = "tripouille";
	size_t	size1 = ft_strlcat(dest1, "42", 13);
	size_t	size2 = strlcat(dest2, "42", 13);
	printf("My String: %s\n My Size: %zu\n", dest1, size1);
	printf("Original String: %s\n Original Size: %zu\n", dest2, size2);
}
*/
