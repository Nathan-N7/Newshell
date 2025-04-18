/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:48:46 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/18 05:08:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_param(va_list params, char const c, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(params, int), fd));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(params, char *), fd));
	else if (c == 'p')
		return (ft_putpointer(va_arg(params, void *)));
	else if (c == 'd')
		return (ft_putnbr_fd(va_arg(params, int), fd));
	else if (c == 'i')
		return (ft_putnbr_fd(va_arg(params, int), fd));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(params, int), "0123456789"));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(params, int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(params, int), "0123456789ABCDEF"));
	else
		return (ft_putchar (c));
}

int	my_printf_fd(char const *s, int fd, ...)
{
	va_list	params;
	int		i;
	int		len;

	if (!s)
		return (-1);
	i = 0;
	len = 0;
	va_start(params, fd);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			len += print_param(params, s[i], fd);
			i++;
		}
		else
		{
			len += write(fd, s + i, 1);
			i++;
		}
	}
	va_end(params);
	return (len);
}
