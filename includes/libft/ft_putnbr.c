/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:00:49 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/26 13:55:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		number_size;
	char	number;

	number_size = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		number_size += write (1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		number_size += ft_putnbr(n / 10);
		number_size += ft_putnbr(n % 10);
	}
	else
	{
		number = n + '0';
		number_size += write(1, &number, 1);
	}
	return (number_size);
}
