/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:56 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/14 11:56:24 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_unsetenv(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[1] && handler.env[i])
	{
		if (ft_strncmp(handler.env[i], av[1], ft_strlen(av[1]) - 1) == 0)
		{
			ft_strdel(handler.env + i);
			j = 1;
		}
		handler.env[i] = handler.env[i + j];
		i++;
	}
	if (i != 0)
		return (0);
	return (-1);
}
