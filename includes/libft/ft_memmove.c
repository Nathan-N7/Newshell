/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:52:17 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/12 12:08:12 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (dest == NULL)
		return (NULL);
	if (d < s)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		return (dest);
	}
}
/*
int	main(void)
{
	char	str[10] = "Start stop";
	
	ft_memmove(str, "Frame", 5);
	printf("%s", str);
}
*/
