/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:40:07 by lbarreto          #+#    #+#             */
/*   Updated: 2024/12/10 14:11:35 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar(char c);
int	ft_putnbr(int n);
int	ft_putstr(char const *str);
int	ft_putnbr_base(unsigned int n, char *base);
int	ft_putpointer(void *ptr);
int	my_printf(char const *s, ...);

#endif
