/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_termcap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 19:05:59 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/17 13:37:18 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include "sh.h"

static void		add_first(t_line *list, t_line *tmp, char c, int *cursor);

static void		add_process(t_line *list, t_line *tmp, char *c, int rank)
{
	tmp->data = c[rank];
	tmp->prev = list;
	tmp->next = 0;
	tmp->nb = list->nb + 1;
	if (list->next)
	{
		list->next->prev = tmp;
		tmp->next = list->next;
	}
	list->next = tmp;
	verif_nb(list);
}

static void		add_list(t_line *list, char *c, int rank, int *cursor)
{
	t_line				*tmp;

	if (c[rank] == '\n' || (tmp = ft_memalloc(sizeof(t_line))) == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (*cursor > 0)
		list = obtain_list(*cursor - 1, list);
	else
	{
		add_first(list, tmp, c[rank], cursor);
		return ;
	}
	add_process(list, tmp, c, rank);
	*cursor = *(cursor) + 1;
	if (c[rank + 1])
		add_list(list, c, rank + 1, cursor);
	else
	{
		tputs(tgetstr("im", NULL), 1, tputs_putchar);
		ft_putchar(c[rank]);
		tputs(tgetstr("ei", NULL), 1, tputs_putchar);
	}
}

static void		create_list(t_line *list, char *c, int *cursor)
{
	list->data = c[0];
	list->prev = 0;
	list->next = 0;
	list->nb = 0;
	*cursor = *(cursor) + 1;
	if (c[1])
		add_list(list, c, 1, cursor);
	else
	{
		tputs(tgetstr("im", NULL), 1, tputs_putchar);
		ft_putchar(c[0]);
		tputs(tgetstr("ei", NULL), 1, tputs_putchar);
	}
}

static void		add_first(t_line *list, t_line *tmp, char c, int *cursor)
{
	tmp->data = list->data;
	tmp->next = list->next;
	tmp->prev = list;
	tmp->nb = 1;
	list->prev = 0;
	list->next = tmp;
	list->data = c;
	list->nb = 0;
	verif_nb(list);
	*cursor = *(cursor) + 1;
	tputs(tgetstr("im", NULL), 1, tputs_putchar);
	ft_putchar(c);
	tputs(tgetstr("ei", NULL), 1, tputs_putchar);
}

void			modif_list(t_line *list, char *c, int *cursor)
{
	if (cmp_key(c, cursor, list))
		return ;
	if (list->data)
		add_list(list, c, 0, cursor);
	else
		create_list(list, c, cursor);
	if (*cursor != list_len(list))
		print_rest(*cursor, list);
}
