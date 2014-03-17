/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 19:11:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/17 13:08:43 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sh.h"


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
