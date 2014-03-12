/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:21 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/12 16:36:46 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_env(char **av)
{
	int	i;

	i = 0;
	if (!av[1])
	{
		while (handler.environ[i])
		{
			ft_putendl(handler.environ[i]);
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
		// else if (ft_strcmp(av[1], "-i") == 0)
	// {
	// 	if (av[2])
	// 		ft_sh1(av + 2, NULL);
	// }
	return (0);
}
