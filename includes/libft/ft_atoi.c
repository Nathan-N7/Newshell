/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:10:35 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/15 14:47:52 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int		nbr;
	int		i;
	int		n;

	nbr = 0;
	i = 0;
	n = 1;
	while (nptr[i] == '\n' || nptr[i] == '\t' || nptr[i] == '\r'
		|| nptr[i] == 127 || nptr[i] == ' '
		|| nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
	{
		n = -n;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * n);
}
/*
#include "libft.h"

int	main (void)
{
	printf("My Atoi: %d\n", ft_atoi(""));
	printf("Original Atoi: %d", atoi(""));
}
*/
