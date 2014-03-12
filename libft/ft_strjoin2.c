/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 14:54:00 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/12 14:55:31 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin2(char **str1, char const *str2)
{
	char	*tmp;

	tmp = ft_strjoin(*str1, str2);
	ft_strdel(&(*str1));
	*str1 = ft_strdup(tmp);
	ft_strdel(&tmp);
}
