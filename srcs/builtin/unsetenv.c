/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:56 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 16:19:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			find_env(char *s)
{
	int		i;

	i = 0;
	while (g_handler.env[i])
	{
		if (ft_strncmp(g_handler.env[i], s, ft_strlen(s)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			builtin_unsetenv(char **av)
{
	int		i;
	int		j;
	int		index;
	char	**tab;

	i = 0;
	j = 0;
	if (!av[1])
		return (-1);
	if ((index = find_env(av[1])) == -1)
		return (0);
	tab = (char **)ft_memalloc(sizeof(char *) * ft_tablen(g_handler.env));
	if (!tab)
		return (-42);
	while (g_handler.env[i])
	{
		if (index != i)
			tab[j++] = ft_strdup(g_handler.env[i]);
		i++;
	}
	ft_free_tab(&g_handler.env);
	g_handler.env = tab;
	return (0);
}
