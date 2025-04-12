/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:52:02 by lbarreto          #+#    #+#             */
/*   Updated: 2024/10/16 11:44:53 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_start;

	temp_start = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp_start->next != NULL)
		temp_start = temp_start->next;
	temp_start->next = new;
}
/*
int	main(void)
{
	t_list	*list1;
	t_list	*list2;
	t_list	*list3;

	list1 = ft_lstnew("Fourty");
	list2 = ft_lstnew("Two");
	list3 = ft_lstnew("Ecole");
	ft_lstadd_back(&list1, list2);
	ft_lstadd_back(&list1, list3);
	printf("%s", (char *)list1 -> content);
	printf(" %s", (char *)list1 -> next -> content);
	printf(" %s", (char *)list1 -> next -> next -> content);
}
*/
