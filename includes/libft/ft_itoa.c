/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:03:34 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/10 15:55:01 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	get_number(int *n)
{
	char	number;

	if (*n < 0)
		number = -(*n % 10) + '0';
	else
		number = (*n % 10) + '0';
	*n = *n / 10;
	return (number);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_number_size(n) + 1;
	if (n < 0)
		len++;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	str[len - 1] = '\0';
	if (n >= 0)
	{
		while (len-- > 1)
			str[len - 1] = get_number(&n);
	}
	else
	{
		str[0] = '-';
		while (len-- > 2)
			str[len - 1] = get_number(&n);
	}
	return (str);
}
/*
int	main(void)
{
	printf("%s", ft_itoa());
}
*/
