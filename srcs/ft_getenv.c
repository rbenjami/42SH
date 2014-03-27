/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:14:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 16:18:52 by rbenjami         ###   ########.fr       */
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
	while (g_handler.env[i]
		&& ft_strncmp(g_handler.env[i], tmp, ft_strlen(tmp)))
		i++;
	if (g_handler.env[i])
	{
		length = ft_strlen(tmp);
		ft_strdel(&tmp);
		return (ft_strdup(&g_handler.env[i][length]));
	}
	else
	{
		ft_strdel(&tmp);
		return (NULL);
	}
}
