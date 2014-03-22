/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:21 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/14 23:07:43 by rbenjami         ###   ########.fr       */
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
		error("42sh: env: illegal option -- %s\nusage: env [-i] \
			[name=value ...] [utility [argument ...]]", av[1] + 1);
	}
	return (0);
}
