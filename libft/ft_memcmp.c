/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 10:23:09 by rbenjami          #+#    #+#             */
/*   Updated: 2013/11/20 10:25:31 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void* s1, const void* s2, size_t n)
{
	if (n > 0)
	{
		while (--n && *(char *)s1 == *(char *)s2)
		{
			s1 = (char*)s1 + 1;
			s2 = (char*)s2 + 1;
		}
		return (*((unsigned char*)s1) - *((unsigned char*)s2));
	}
	return (0);
}
