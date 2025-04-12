/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:26 by lbarreto          #+#    #+#             */
/*   Updated: 2025/01/07 16:09:43 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcpy(join + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (s1 != NULL)
	free(s1);
	free(s2);
	return (join);
}
/*
int	main(void)
{
	printf("%s", ft_strjoin("tripouille", "42"));
}
*/
