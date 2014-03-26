/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 19:03:38 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 19:46:03 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include "sh.h"

void	turn_on(struct termios *term)
{
	char	buffer[2048];

	if (tgetent(buffer, getenv("TERM")) < 1)
	{
		write(2, "TERM: not found\n", 16);
		exit(0);
	}
	tcgetattr(0, term);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	tcsetattr(0, 0, term);
}

void	turn_off(struct termios *term)
{
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	tcsetattr(0, 0, term);
}
