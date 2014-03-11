/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:13:04 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/11 16:59:35 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char		*create_var(char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
		i++;
	str[i] = '\0';
	return (str);
}

static int		smart_print(char *str)
{
	int		wr;
	int		i;
	char	*var;

	i = 0;
	wr = 0;
	var = NULL;
	while (str[i] && str[i] != '$')
	{
		wr++;
		write(1, &str[i], 1);
		i++;
	}
	var = str[i + 1] ? ft_getenv(create_var(&str[i + 1])) : NULL;
	wr = var ? wr + 1 : wr;
	if (var)
		ft_putstr(var);
		if (str[i + 1])
		i++;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$')
		i++;
	if (str[i])
		write(1, &str[i++], 1);
	if (str[i])
		smart_print(&str[i]);
	return (wr);
}

int				builtin_echo(char **argv)
{
	int		i;
	int		dollar;
	int		wr;

	dollar = 0;
	wr = 0;
	if (argv[1])
	{
		i = (ft_strcmp(argv[1], "-n") == 0) ? 2 : 1;
		while (argv[i])
		{
			wr += smart_print(argv[i]);
			if (argv[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(argv[1], "-n") == 0)
			ft_putstr("\033[7m%\033[m");
		write(1, "\n", 1);
	}
	if (!argv[1] || wr == 0)
		write(1, "\n", 1);
	exit(0);
	return (-1);
}
