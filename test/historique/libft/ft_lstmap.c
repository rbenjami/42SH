/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazian <akazian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 11:37:28 by akazian           #+#    #+#             */
/*   Updated: 2013/11/28 14:28:15 by akazian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list * (*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*tmp;
	t_list	*next;
	t_list	*tmp2;

	tmp = lst;
	newlist = ft_lstnew(tmp->content, tmp->content_size);
	f(newlist);
	if (tmp->next != NULL)
	{
		tmp = tmp->next;
		tmp2 = newlist;
	}
	while (tmp != NULL)
	{
		next = tmp->next;
		tmp2->next = ft_lstnew(tmp->content, tmp->content_size);
		tmp = next;
		f(tmp2->next);
		tmp2 = tmp2->next;
	}
	return (newlist);
}
