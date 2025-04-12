/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:24:49 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/10 12:20:24 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (srclen);
	while ((i < size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}
/*
int	main(void)
{
	char	str[10] = "abc";
	int		size;
	
	size = strlcpy(str, "testing", 0);
	printf("size: %d - string: %s", size, str);
}
*/
