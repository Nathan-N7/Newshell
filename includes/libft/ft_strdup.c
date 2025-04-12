/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:53:21 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/10 12:22:28 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (!dup)
		return (NULL);
	ft_memmove(dup, s, len);
	return (dup);
}
/*
int	main(void)
{
	printf("%s\n", ft_strdup("Test 42"));
}
*/
