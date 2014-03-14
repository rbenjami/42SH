/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:26:15 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 22:59:49 by rbenjami         ###   ########.fr       */
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
				ft_putchar('%');
			else if (*msg == 'c')
				ft_putchar(va_arg(ap, int));
			else if (*msg == 's')
				ft_putstr(va_arg(ap, char*));
			else if (*msg == 'd')
				ft_putnbr(va_arg(ap, int));
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
