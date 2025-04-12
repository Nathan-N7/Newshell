/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:26 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/12 12:57:31 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if ((unsigned char)c == 0)
	{
		while (*s)
			s++;
		return ((char *) s);
	}
	else
	{
		while (*s)
		{
			if ((unsigned char)c == *s)
				return ((char *) s);
			s++;
		}
		return (NULL);
	}
}
/*
int	main(void)
{
	printf("%s", strchr("abcde", 'c'));
}
*/
