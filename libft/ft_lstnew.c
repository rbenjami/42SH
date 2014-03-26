/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 18:49:38 by akazian           #+#    #+#             */
/*   Updated: 2014/03/26 16:56:12 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(t_list));
	if (!newlst)
		return (NULL);
	if (!content)
	{
		newlst->content = NULL;
		newlst->content_size = 0;
		newlst->next = NULL;
		return (newlst);
	}
	newlst->content = (void *)content;
	newlst->content_size = content_size;
	newlst->next = NULL;
	return (newlst);
}
