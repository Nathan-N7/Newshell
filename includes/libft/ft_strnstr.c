/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:50:51 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/15 14:48:18 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find(const char *big, const char *little, size_t len, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (i <= len)
	{
		if (little[k] == '\0')
			return (1);
		if (big[j] == little[k])
			k++;
		else
			return (0);
		j++;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (little == NULL || big == NULL)
		return ((char *)big);
	if (little[0] == 0 && big[0] == 0)
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (find(big + i, little, len, i) == 1)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s", ft_strnstr("aaabcabcd", "aabc", -1));
}
*/
