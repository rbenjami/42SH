/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:21 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/14 18:40:35 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_env(char **av)
{
	int	i;

	i = 0;
	if (!av[1])
	{
		while (handler.env[i])
		{
			ft_putendl(handler.env[i]);
			i++;
		}
	}
	else
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putendl_fd(av[1] + 1, 2);
		ft_putstr_fd("usage: env [-i] [name=value ...]", 2);
		ft_putendl_fd("[utility [argument ...]]", 2);
	}
	return (0);
}
