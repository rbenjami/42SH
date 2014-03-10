/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:14:38 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/10 18:14:52 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv(const char *name)
{
	int				i;

	i = 0;
	name = ft_strjoin(name, "=");
	while (environ[i] && ft_strncmp(environ[i], name, ft_strlen(name)))
		i++;
	if (environ[i])
		return (&environ[i][ft_strlen(name)]);
	else
	{
		write(2, name, (ft_strlen(name) - 1));
		ft_putendl_fd(": not found", 2);
		return (NULL);
	}
}
