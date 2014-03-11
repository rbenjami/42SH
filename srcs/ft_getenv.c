/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:14:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/11 15:35:42 by rbenjami         ###   ########.fr       */
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
	while (handler.environ[i] && ft_strncmp(handler.environ[i], tmp, ft_strlen(tmp)))
		i++;
	if (handler.environ[i])
	{
		lenth = ft_strlen(tmp);
		ft_strdel(&tmp);
		return (&handler.environ[i][lenth]);
	}
	else
	{
		ft_strdel(&tmp);
		return (NULL);
	}
}
