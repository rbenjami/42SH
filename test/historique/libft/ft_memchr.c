/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 10:23:09 by rbenjami          #+#    #+#             */
/*   Updated: 2013/12/25 15:01:46 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cp;

	cp = (unsigned char *) s;
	if (n)
	{
		while (n)
		{
			if (*cp++ == (unsigned char) c)
				return (cp - 1);
			n--;
		}
	}
	return (0);
}
