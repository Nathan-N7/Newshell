/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:24:21 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/22 10:06:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	mini_putnbr_base(unsigned long n, char *base)
{
	unsigned long	number_size;
	int				len;

	number_size = 0;
	len = 0;
	while (base[number_size])
		number_size++;
	if (n >= number_size)
	{
		len += mini_putnbr_base(n / number_size, base);
		len += mini_putnbr_base(n % number_size, base);
	}
	else
		len += write(1, base + n, 1);
	return (len);
}

int	ft_putpointer(void *ptr)
{
	unsigned long	number;
	int				len;	

	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	len = 0;
	number = (unsigned long)ptr;
	len += write(1, "0x", 2);
	len += mini_putnbr_base(number, "0123456789abcdef");
	return (len);
}
