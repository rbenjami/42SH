/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 12:07:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 12:25:10 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include "sh.h"

void	print_error(char *logname, char	*pwd, char *home)
{
	if (handler.cmd == 0)
		ft_putstr("\033[m\033[32m");
	else
	{
		ft_putstr("\033[m\033[31m ");
		ft_putnbr(handler.cmd);
	}
	ft_putstr(" ~> \033[m");
	ft_strdel(&home);
	ft_strdel(&logname);
	ft_strdel(&pwd);
}

void	prompt(void)
{
	int		i;
	char	*logname;
	char	*pwd;
	char	*home;

	i = 0;
	logname = NULL;
	pwd = NULL;
	home = NULL;
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, tputs_putchar);
	ft_putstr("\033[40m");
	if ((logname = ft_getenv("LOGNAME")))
		ft_putstr(logname);
	ft_putstr("\033[m\033[44m\033[30m");
	if ((pwd = ft_getenv("PWD"))
		&& (home = ft_getenv("HOME"))
		&& !ft_strncmp(pwd, home, ft_strlen(home)))
	{
		ft_putstr("~");
		i = ft_strlen(home);
	}
	if (pwd)
		ft_putstr(pwd + i);
	print_error(logname, pwd, home);
}
