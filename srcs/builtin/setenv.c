/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:39 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/22 18:35:52 by killer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_add(char *name, char *value)
{
	char	**tab;
	int		length;

	length = ft_tablen(handler.env);
	tab = ft_cpytab(handler.env, length + 1);
	ft_strjoin2(&name, "=");
	tab[length] = ft_strjoin(name, value);
	tab[length + 1] = NULL;
	ft_free_tab(&handler.env);
	handler.env = tab;
}

int		builtin_setenv(char **av)
{
	int		i;
	char	*tmp;
	int		ov;

	i = 0;
	if (!av[2])
		return (-1);
	ov = (av[3]) ? ft_atoi(av[3]) : 0;
	while (handler.env[i])
	{
		if (ft_strncmp(handler.env[i], av[1], ft_strlen(av[1])) == 0)
		{
			if (ov)
			{
				ft_strdel(handler.env + i);
				tmp = ft_strjoin(av[1], "=");
				handler.env[i] = ft_strjoin(tmp, av[2]);
				ft_strdel(&tmp);
			}
			return (0);
		}
		i++;
	}
	ft_add(av[1], av[2]);
	return (0);
}
