/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:44:54 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/15 12:58:38 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	*list1;
	t_list	*list2;

	list1 = ft_lstnew("Fourty");
	list2 = ft_lstnew("Two");
	list1 -> next = list2;
	printf("%s", (char *)ft_lstlast(list1)->content);
}
*/
