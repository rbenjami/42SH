/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:13:04 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/11 15:23:09 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char		*create_var(char *str, int start)
{
	int		i;
	char	*tmp;

	i = start;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
		i++;
	tmp = ft_strsub(str, start, i - start);
	return (str);
}

static void		smart_print(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] && str[i + 1] && !(var = create_var(str, i)))
	{
		write(1, &str[i], 1);
		smart_print(&str[i + 1]);
	}
	else if (str[i] && (var = ft_getenv(var)) == NULL)
	{
		write(1, &str[i], 1);
		smart_print(&str[i + 1]);
	}
	else if (str[i] && var)
		ft_putstr(var);
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
		i++;
	if (str[i])
		smart_print(&str[i]);
}

int				builtin_echo(char **argv)
{
	int		i;
	int		dollar;

	i = 1;
	dollar = 0;
	if (argv[1])
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			i = 2;
		while (argv[i])
		{
			smart_print(argv[i]);
			if (argv[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(argv[1], "-n") == 0)
			ft_putstr("\033[7m%\033[m");
		write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	exit(0);
	return (-1);
}
