/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 19:11:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/16 15:43:15 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sh.h"

void	print_list(t_line *list, int cursor)
{
	float				back;
	float				i;
	struct winsize		ws;
	int					line;
// SI ON ARRIVE A WIDTH ON REVIENT A LA LIGNE PUIS POS = truc % width
	// ON IMPRIME LA SUITE DE LA LISTE A PARTIR DE LA

	ioctl(0, TIOCGWINSZ, &ws);
	i = len_prompt() + cursor;
	line = (cursor + i) / ws.ws_col;
	back = list_len(list) - cursor;
	while (line)
	{
		tputs(tgetstr("up", NULL), 1, tputs_putchar);
		line = !line ? -42 : line - 1;
	}
	cursor = line <= -42 ? len_prompt() + cursor : cursor;
	while (cursor-- > 1)
	{
		if (line > -42)
			tputs(tgetstr("le", NULL), 1, tputs_putchar);
		else
			tputs(tgetstr("nd", NULL), 1, tputs_putchar);

	}
	tputs(tgetstr("cd", NULL), 1, tputs_putchar);
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (list->data == '\t')
			ft_putchar(' ');
		else
			ft_putchar(list->data);
		if (i++ == ws.ws_col)
		{
			i = 0;
			tputs(tgetstr("do", NULL), 1, tputs_putchar);
		}
		list = list->next;
	}
	while (cursor < back)
	{
		tputs(tgetstr("le", NULL), 1, tputs_putchar);
		cursor++;
	}
}

int		len_prompt(void)
{
	int		i;
	char	*pwd;
	char	*home;
	int		len;

	i = 0;
	len = 4;
	pwd = ft_getenv("PWD");
	home = ft_getenv("HOME");
	if (!ft_strncmp(pwd, home, ft_strlen(home)))
	{
		len++;
		i = ft_strlen(home);
	}
	len += ft_strlen(ft_getenv("LOGNAME"));
	len += ft_strlen(pwd + i);
	if (handler.cmd != 0)
		len += ft_strlen(ft_itoa(handler.cmd)) + 1;
	return (len);
}

int		list_len(t_line *list)
{
	int			i;

	i = 0;
	if (list)
	{
		if (!list->data)
			return (-1);
		while (list->prev)
			list = list->prev;
		while (list->next)
		{
			list = list->next;
			i++;
		}
	}
	return (i + 1);
}

t_line		*obtain_list(int cursor, t_line *list)
{
	while (list->prev)
		list = list->prev;
	while (list->next && list->nb != cursor)
		list = list->next;
	return (list);
}

void		verif_nb(t_line *list)
{
	while (list->prev)
		list = list->prev;
	while (list->next)
	{
		if (list->prev)
			list->nb = list->prev->nb + 1;
		else
			list->nb = 0;
		list = list->next;
	}
}

int			ft_match(char *c, char search)
{
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] == search)
			return (1);
		i++;
	}
	return (0);
}
