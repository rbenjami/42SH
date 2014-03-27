/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 12:07:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 12:07:32 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include "sh.h"

void	prompt(int i, char *logname, char *pwd, char *home)
{
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
