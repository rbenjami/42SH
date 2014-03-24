/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:26:15 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/24 17:45:39 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh.h"

/*
**	Error:
**	%c -> char
**	%s -> char*
**	%d -> int
**	%p -> perror
*/

int		ft_putcolored_char(char c, int color)
{
	if (color == BLACK)
		ft_putstr("\033[30m");
	if (color == RED)
		ft_putstr("\033[31m");
	if (color == GREEN)
		ft_putstr("\033[32m");
	if (color == YELLOW)
		ft_putstr("\033[33m");
	if (color == BLUE)
		ft_putstr("\033[34m");
	if (color == MAGENTA)
		ft_putstr("\033[35m");
	if (color == CYAN)
		ft_putstr("\033[36m");
	if (color == WITHE)
		ft_putstr("\033[37m");
	ft_putchar(c);
	ft_putstr("\033[m");
	return (1);
}

int		error(const char *msg, ...)
{
	va_list		ap;

	va_start(ap, msg);
	while (*msg)
	{
		if (*msg == '%')
		{
			msg++;
			if (*msg == '%')
				ft_putchar_fd('%', 2);
			else if (*msg == 'c')
				ft_putchar_fd(va_arg(ap, int), 2);
			else if (*msg == 's')
				ft_putstr_fd(va_arg(ap, char*), 2);
			else if (*msg == 'd')
				ft_putnbr_fd(va_arg(ap, int), 2);
			else if (*msg == 'p')
				perror(va_arg(ap, const char*));
		}
		else
			ft_putcolored_char(*msg, 1);
		msg++;
	}
	va_end(ap);
	return (-42);
}
