/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:21 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/14 14:48:09 by rbenjami         ###   ########.fr       */
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
		ft_putstr_fd("env: illegal option -- ", ERR);
		ft_putendl_fd(av[1] + 1, ERR);
		ft_putstr_fd("usage: env [-i] [name=value ...]", ERR);
		ft_putendl_fd("[utility [argument ...]]", ERR);
	}
	return (0);
}
