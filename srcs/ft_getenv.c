/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:14:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/14 18:39:00 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(const char *name)
{
	int				i;
	int				lenth;
	char			*tmp;

	i = 0;
	tmp = ft_strjoin(name, "=");
	while (handler.env[i] && ft_strncmp(handler.env[i], tmp, ft_strlen(tmp)))
		i++;
	if (handler.env[i])
	{
		lenth = ft_strlen(tmp);
		ft_strdel(&tmp);
		return (&handler.env[i][lenth]);
	}
	else
	{
		ft_strdel(&tmp);
		return (NULL);
	}
}
