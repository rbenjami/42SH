/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:50:44 by rbenjami          #+#    #+#             */
/*   Updated: 2014/01/14 17:59:14 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_saveitoa(int size, unsigned int n, char *nb, int neg)
{
	int			j;

	j = 0;
	if (neg)
	{
		nb[j] = '-';
		j++;
	}
	while (size > 0)
	{
		nb[j] = (n / size) + '0';
		n = n % size;
		size = size / 10;
		j++;
	}
	nb[j] = '\0';
	return (nb);
}

char			*ft_itoa(int n)
{
	int				size;
	unsigned int	i;
	unsigned int	n2;
	int				neg;
	char			*nb;

	size = 1;
	neg = 0;
	if (n < 0)
	{
		i = n * -1;
		neg++;
	}
	else
		i = n;
	n2 = i;
	n = 0;
	while (i / 10 > 0)
	{
		size *= 10;
		i = i / 10;
		n++;
	}
	nb = ft_strnew(n + neg);
	return (ft_saveitoa(size, n2, nb, neg));
}
