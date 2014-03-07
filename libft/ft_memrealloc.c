/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 14:46:50 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/07 18:14:28 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrealloc(void **ptr, size_t size, size_t new_size)
{
	void	*mem;

	if (size == new_size)
		return (*ptr);
	mem = ft_memalloc(new_size);
	if (mem)
	{
		ft_memcpy(mem, *ptr, MIN(size, new_size));
		ft_memdel(ptr);
	}
	return (mem);
}
