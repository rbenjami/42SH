/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazian <akazian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 11:17:21 by akazian           #+#    #+#             */
/*   Updated: 2013/11/28 11:35:00 by akazian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*next;

	tmp = lst;
	while (tmp != NULL)
	{
		next = tmp->next;
		f(tmp);
		tmp = next;
	}
}

