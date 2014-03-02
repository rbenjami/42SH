/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 12:31:14 by dsousa            #+#    #+#             */
/*   Updated: 2014/02/28 13:15:07 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "sh.h"

char	*ft_getenv(const char *name)
{
	extern char		**environ;
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
