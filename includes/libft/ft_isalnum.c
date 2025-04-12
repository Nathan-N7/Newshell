/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:39:47 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/16 11:49:48 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int ch)
{
	if ((ch < 97 || ch > 122) && (ch < 48 || ch > 57) && (ch < 65 || ch > 90))
		return (0);
	return (1);
}
/*
#include "libft.h"
#include <stdio.h>

int main(void)
{
    printf("%d", ft_isalnum('9'));

}
*/
