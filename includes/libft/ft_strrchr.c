/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:35:52 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/12 13:04:02 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if (c == 0)
		return ((char *)s + len);
	while (len)
	{
		if ((unsigned char)c == s[len - 1])
			return ((char *)s + len - 1);
		len--;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s", ft_strrchr("abcde", 'a'));
}
*/
