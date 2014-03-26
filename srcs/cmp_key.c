/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 17:11:08 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/26 18:36:57 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sh.h"

void				print_rest(int cursor, t_line *list)
{
	t_ws			ws;
	int				i;

	ioctl(0, TIOCGWINSZ, &ws);
	i = 0;
	list = obtain_list(cursor, list);
	cursor += len_prompt();
	while (list)
	{
		ft_putchar(list->data);
		list = list->next;
		i++;
	}
	if ((cursor % ws.ws_col) != 0)
	{
		if ((cursor % ws.ws_col) > ws.ws_col - i)
			tputs(tgetstr("up", NULL), 1, tputs_putchar);
		i = (cursor % ws.ws_col);
		tputs(tgoto(tgetstr("ch", NULL), 0, i), 1, tputs_putchar);
	}
	else
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, tputs_putchar);
}

void				delete_first(t_line *list)
{
	if (list->next)
	{
		list->data = list->next->data;
		list->next = list->next->next;
		list->prev = NULL;
		verif_nb(list);
	}
	else
		list->data = 0;
}

int					cmp_key(char *key, int *cursor, t_line *list, t_ctrl_h *h)
{
	int				i;
	static t_key	tbl[7] =

	{
	{UP, &ft_up},
	{LEFT, &ft_left},
	{RIGHT, &ft_right},
	{DOWN, &ft_down},
	{DEL, &ft_del},
	{SUPR, &ft_supr},
	{0, 0}
	};
	i = 0;
	while (tbl[i].key)
	{
		if (*(unsigned int *)key == (unsigned int)tbl[i].key)
		{
			tbl[i].f(key, cursor, list, h);
			return (1);
		}
		i++;
	}
	i = ft_isprint(key[0]) ? 0 : 1;
	return (i);
}
