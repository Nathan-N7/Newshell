/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:01:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/02/21 21:02:51 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *nptr)
{
	long	nbr;
	int		i;
	long	n;

	nbr = 0;
	i = 0;
	n = 1;
	while (nptr[i] == '\n' || nptr[i] == '\t' || nptr[i] == '\r'
	    || nptr[i] == ' '	|| nptr[i] == '\v' || nptr[i] == '\f')
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