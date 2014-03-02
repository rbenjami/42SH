/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:21:39 by rbenjami          #+#    #+#             */
/*   Updated: 2014/01/13 15:46:39 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_islower(int c)
{
	return ((c >= 'a') && (c <= 'z'));
}

static int		ft_isupper(int c)
{
	return ((c >= 'A') && (c <= 'Z'));
}

int				ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
