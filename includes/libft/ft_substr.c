/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:32:59 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/14 13:49:32 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t n1, size_t n2)
{
	size_t	min;

	min = n1;
	if (min > n2)
		min = n2;
	return (min);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	size = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= size)
		return ((char *)ft_calloc(1, 1));
	size -= start;
	size = min(size, len);
	sub = (char *)malloc((size + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_memmove(sub, s + start, size);
	sub[size] = '\0';
	return (sub);
}
/*
int	main(void)
{
	printf("%s", ft_substr("testing", 3, 20));
}
*/
