/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:13:04 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/10 18:42:28 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_echo(char **argv)
{
	int		i;
	char	*str;

	i = 1;
	if (argv[1])
	{
		while (argv[i])
		{
			if (argv[i][0] == '$' && argv[i][1] && (str = ft_getenv(&argv[i][1])))
				ft_putstr(str);
			else
				ft_putstr(argv[i]);
			if (argv[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(argv[1], "-n") != 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (-1);
}
