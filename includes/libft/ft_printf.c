/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:15:41 by lbarreto          #+#    #+#             */
/*   Updated: 2024/12/10 13:56:05 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_param(va_list params, char const c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(params, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(params, char const *)));
	else if (c == 'p')
		return (ft_putpointer(va_arg(params, void *)));
	else if (c == 'd')
		return (ft_putnbr(va_arg(params, int)));
	else if (c == 'i')
		return (ft_putnbr(va_arg(params, int)));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(params, int), "0123456789"));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(params, int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(params, int), "0123456789ABCDEF"));
	else
		return (ft_putchar (c));
}

int	my_printf(char const *s, ...)
{
	va_list	params;
	int		i;
	int		len;

	if (!s)
		return (-1);
	i = 0;
	len = 0;
	va_start(params, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += print_param(params, s[i]);
			i++;
		}
		else
		{
			len += write(1, s + i, 1);
			i++;
		}
	}
	va_end(params);
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	ft_printf("My len: %d\n", ft_printf("%p", NULL));
	printf("Original len: %d\n", printf("%p", NULL));
}
*/
