/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconstjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:24:47 by lbarreto          #+#    #+#             */
/*   Updated: 2025/05/18 17:25:38 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconstjoin(char const *s1, char const *s2)
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
    if (s2 != NULL)
        free(s2);
	return (join);
}
