/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 14:23:16 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/10 18:00:59 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


int		builtin_cd(char **av)
{
	ft_putendl(av[0]);
	exit(1);
	return (1);
}

int		builtin_echo(char **av)
{
	ft_putendl(av[0]);
	exit(1);
	return (1);
}

int		builtin_exit(char **av)
{
	ft_putendl(av[0]);
	exit(1);
	return (1);
}

int		builtin_env(char **av)
{
	ft_putendl(av[0]);
	exit(1);
	return (1);
}

int		builtin_setenv(char **av)
{
	ft_putendl(av[0]);
	exit(1);
	return (1);
}

int		builtin_unsetenv(char **av)
{
	ft_putendl(av[0]);
	exit(1);
	return (1);
}

int		(*find_builtin(char *cmd))(char **)
{
	int					i;
	static t_find		tbl[7] =
	{
		{"cd", &builtin_cd},
		{"echo", &builtin_echo},
		{"exit", &builtin_exit},
		{"env", &builtin_env},
		{"setenv", &builtin_setenv},
		{"unsetenv", &builtin_unsetenv},
		{NULL, NULL}
	};

	i = 0;
	while (tbl[i].f && ft_strcmp(tbl[i].cmd, cmd))
		i++;
	if (tbl[i].f)
		return (tbl[i].f);
	else
		return (NULL);
}
