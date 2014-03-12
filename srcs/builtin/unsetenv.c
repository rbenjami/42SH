/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:56 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/12 18:30:46 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_unsetenv(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[1] && handler.environ[i])
	{
		if (ft_strncmp(handler.environ[i], av[1], ft_strlen(av[1]) - 1) == 0)
		{
			ft_strdel(handler.environ + i);
			j = 1;
		}
		handler.environ[i] = handler.environ[i + j];
		i++;
	}
	if (i != 0)
		return (0);
	return (-1);
}
