/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:10:53 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/11 10:44:23 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*
int	main(void)
{
	t_list *list1;
	t_list *list2;
	t_list *list3;

	list1 = ft_lstnew("My");
	list2 = ft_lstnew("little");
	list3 = ft_lstnew("test");
	list1 -> next = list2;
	list2 -> next = list3;
	printf("%d", ft_lstsize(list1));
}
*/
