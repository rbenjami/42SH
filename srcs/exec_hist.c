/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 18:37:14 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/26 19:33:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sh.h"

static void		save_str(char *str, t_line *list, int *cursor)
{
	int				i;

	i = 0;
	*cursor = 0;
	list->data = 0;
	if (!list->data)
	{
		create_list(list, str, cursor);
		return ;
	}
	while (list->next && str[i])
	{
		list->data = str[i];
		list = list->next;
		*cursor = *cursor + 1;
		i++;
	}
	if (!list->next && str[i])
		add_list(list, str, i, cursor);
	else if (!str[i] && list->next)
		freelist(list);
}

static void		print_hist(int *cursor, char *str, t_ctrl_h *h, t_line *l)
{
	int				nb;
	t_ws			ws;

	ioctl(0, TIOCGWINSZ, &ws);
	nb = (*cursor + len_prompt()) / ws.ws_col;
	while (nb-- > 0)
		tputs(tgetstr("up", NULL), 1, tputs_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, len_prompt()), 1, tputs_putchar);
	tputs(tgetstr("cd", NULL), 1, tputs_putchar);
	if (str)
	{
		save_str(str, l, cursor);
		*cursor = ft_strlen(str);
	}
	else
	{
		h->nb = -1;
		*cursor = 0;
		l->data = 0;
		if (l->next)
		{
			freelist(l);
			l->next = 0;
		}
	}
}

void			ft_down(char *key, int *cursor, t_line *list, t_ctrl_h *h)
{
	t_hist			*elem;
	int				nb;
	t_ws			ws;

	if (h->nb <= 0)
	{
		print_hist(cursor, NULL, h, list);
		return ;
	}
	h->nb--;
	nb = h->nb;
	ioctl(0, TIOCGWINSZ, &ws);
	elem = h->last;
	while (elem->prev && nb > 0)
	{
		elem = elem->prev;
		nb--;
	}
	if (elem->data && key && list)
		print_hist(cursor, elem->data, h, list);
	*cursor = ft_strlen(elem->data);
	h->unused = 0;
}

void			ft_up(char *key, int *cursor, t_line *list, t_ctrl_h *h)
{
	t_hist			*elem;
	int				nb;
	t_ws			ws;

	if (h->unused == 42)
		return ;
	h->nb++;
	nb = h->nb;
	ioctl(0, TIOCGWINSZ, &ws);
	elem = h->last;
	while (elem->prev && nb > 0)
	{
		elem = elem->prev;
		nb--;
	}
	if (nb > 1)
		return ;
	if (elem->data && key && list)
		print_hist(cursor, elem->data, h, list);
	if (!elem->prev)
		h->unused = 42;
}
