/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damerica <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 19:34:09 by damerica          #+#    #+#             */
/*   Updated: 2019/09/18 17:39:31 by damerica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list1;
	t_list *list2;

	if (!lst || !f)
		return (NULL);
	list1 = f(lst);
	list2 = list1;
	while (lst->next)
	{
		lst = lst->next;
		if (!(list1->next = f(lst)))
		{
			free(list1->next);
			return (NULL);
		}
		list1 = list1->next;
	}
	return (list2);
}
