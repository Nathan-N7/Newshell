/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:50:26 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/12 12:53:11 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (str1 == NULL || str2 == NULL || n == 0)
		return (0);
	else
	{
		i = 0;
		while (str1[i] == str2[i] && i < n - 1)
			i++;
		return (str1[i] - str2[i]);
	}
}
/*
int	main(void)
{
	printf("%d", memcmp("abcde", "abc", 0));
}
*/	
