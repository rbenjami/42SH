/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 19:06:44 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/17 12:43:48 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sh.h"

void	delete_first(t_line *list)
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

void	exec_key(char *key, int *cursor, t_line *list)
{
	t_line				*tmp;
	struct winsize		ws;
	int					tmp_cursor;

	tputs(tgetstr("im", NULL), 1, tputs_putchar);
	ioctl(0, TIOCGWINSZ, &ws);
	tmp = NULL;
	if (*(unsigned int *)key == LEFT && *cursor > 0)
	{
		*cursor = *(cursor) - 1;
		tmp_cursor = *cursor + len_prompt();
		if (tmp_cursor % ws.ws_col == ws.ws_col - 1)
		{
			tputs(tgetstr("up", NULL), 1, tputs_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, tmp_cursor), 1, tputs_putchar);
		}
		else
			ft_putstr(key);
	}
	else if (*(unsigned int *)key == RIGHT && *cursor < list_len(list))
	{
		*cursor = *(cursor) + 1;
		if (*cursor + len_prompt() == ws.ws_col)
			tputs(tgetstr("do", NULL), 1, tputs_putchar);
		else
			tputs(tgetstr("nd", NULL), 1, tputs_putchar);
	}
	else if (*(unsigned int *)key == DEL && *cursor > 0)
	{
		*cursor = *(cursor) - 1;
		tmp_cursor = *cursor + len_prompt();
		if (tmp_cursor % ws.ws_col == ws.ws_col - 1)
		{
			tputs(tgetstr("up", NULL), 1, tputs_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, tmp_cursor), 1, tputs_putchar);
		}
		else
			tputs(tgetstr("le", NULL), 1, tputs_putchar);
		tputs(tgetstr("dc", NULL), 1, tputs_putchar);
		if (*cursor <= 0)
		{
			delete_first(list);
			tputs(tgetstr("ei", NULL), 1, tputs_putchar);
			tputs(tgetstr("cd", NULL), 1, tputs_putchar);
			print_rest(*cursor, list);
			return ;
		}
		tmp = obtain_list(*cursor, list);
		if (tmp && tmp->prev && tmp->prev->next)
			tmp->prev->next = tmp->next;
		if (tmp && tmp->next && tmp->next->prev)
			tmp->next->prev = tmp->prev;
		if (tmp)
			free(tmp);
		verif_nb(list);
		tputs(tgetstr("cd", NULL), 1, tputs_putchar);
		print_rest(*cursor, list);
	}
	else if (*(unsigned int *)key == SUPR && *cursor < list_len(list))
	{
		tputs(tgetstr("dc", NULL), 1, tputs_putchar);
		if (*cursor == 0)
		{
			delete_first(list);
			tputs(tgetstr("ei", NULL), 1, tputs_putchar);
			tputs(tgetstr("cd", NULL), 1, tputs_putchar);
			print_rest(*cursor, list);
			return ;
		}
		tmp = obtain_list(*cursor, list);
		if (tmp && tmp->prev && tmp->prev->next)
			tmp->prev->next = tmp->next;
		if (tmp && tmp->next && tmp->next->prev)
			tmp->next->prev = tmp->prev;
		if (tmp)
			free(tmp);
		verif_nb(list);
		tputs(tgetstr("cd", NULL), 1, tputs_putchar);
		if (*cursor < list_len(list))
			print_rest(*cursor, list);
	}
	tputs(tgetstr("ei", NULL), 1, tputs_putchar);
}
