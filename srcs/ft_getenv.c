/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:14:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/24 17:45:43 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(const char *name)
{
	int				i;
	int				length;
	char			*tmp;

	length = 0;
	i = 0;
	tmp = ft_strjoin(name, "=");
	while (handler.env[i] && ft_strncmp(handler.env[i], tmp, ft_strlen(tmp)))
		i++;
	if (handler.env[i])
	{
		length = ft_strlen(tmp);
		ft_strdel(&tmp);
		return (ft_strdup(&handler.env[i][length]));
	}
	else
	{
		ft_strdel(&tmp);
		return (NULL);
	}
}
