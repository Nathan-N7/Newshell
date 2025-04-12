/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:55:21 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/14 14:21:55 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_char(char chr, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (chr == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	int		len;

	while (find_char(s1[0], set) == 1)
		s1++;
	len = ft_strlen(s1);
	while (find_char(s1[len - 1], set) == 1 && *s1)
		len--;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	ft_memmove(trimmed_str, s1, len);
	trimmed_str[len] = '\0';
	return (trimmed_str);
}
/*
int	main(void)
{
	printf("%s", ft_strtrim(" - test - ", "- "));
}
*/
