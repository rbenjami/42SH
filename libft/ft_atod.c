/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 15:56:51 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/05 15:24:34 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_atod(char *str)
{
	int				i;
	unsigned int	j;
	double			res;
	double			tmp;

	i = 0;
	if (!ft_isdigit(str[i]) && str[i] != '-')
		return (0);
	res = ft_atoi(str);
	while (str[i] != '.')
		i++;
	tmp = ft_atoi(&str[i + 1]);
	j = 0;
	while (j++ < ft_strlen(&str[i + 1]))
		tmp /= 10;
	res += tmp;
	return (res);
}
