/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:46:56 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/22 16:46:24 by killer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		find_env(char *s)
{
	int	i;

	i = 0;
	while (handler.env[i])
	{
		if (ft_strncmp(handler.env[i], s, ft_strlen(s)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
int		builtin_unsetenv(char **av)
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
	tab = (char **)ft_memalloc(sizeof(char *) * ft_tablen(handler.env));
	while (handler.env[i])
	{
		if (index != i)
			tab[j++] = ft_strdup(handler.env[i]);
		i++;
	}
	ft_free_tab(&handler.env);
	handler.env = tab;
	return (0);
}
