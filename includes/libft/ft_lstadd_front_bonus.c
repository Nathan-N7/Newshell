/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:49:44 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/11 11:18:42 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*list1;
	t_list	*list2;
	t_list	*list3;

	list1 = ft_lstnew("test");
	list2 = ft_lstnew("little");
	list3 = ft_lstnew("My");
	ft_lstadd_front(&list1, list2);
	ft_lstadd_front(&list1, list3);
	printf("%s", (char *)list1->content);
	printf(" %s", (char *) list1->next->content);
	printf(" %s", (char *) list1->next->next->content);
}
*/
