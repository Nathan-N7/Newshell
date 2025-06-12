/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrodri <natrodri@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:40:07 by lbarreto          #+#    #+#             */
/*   Updated: 2025/06/12 15:38:27 by natrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putnbr(int n);
int	ft_putstr(char const *str);
int	ft_putnbr_base(unsigned int n, char *base);
int	ft_putpointer(void *ptr);
int	my_printf(char const *s, ...);

#endif
