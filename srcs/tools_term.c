/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 19:11:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 19:37:51 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sh.h"

int			len_prompt(void)
{
	int		i;
	int		len;
	char	*str[4];

	if (g_handler.len)
		return (g_handler.len);
	i = 0;
	len = 4;
	str[1] = ft_getenv("HOME");
	str[0] = ft_getenv("PWD");
	if (str[0] && str[1] && !ft_strncmp(str[0], str[1], ft_strlen(str[1])))
	{
		len++;
		i = ft_strlen(str[1]);
	}
	len += ft_strlen(str[2] = ft_getenv("LOGNAME"));
	len = str[0] ? len + ft_strlen(str[0] + i) : len;
	if (g_handler.cmd != 0)
	{
		len += ft_strlen(str[3] = ft_itoa(g_handler.cmd)) + 1;
		ft_strdel(&str[3]);
	}
	del_3_str(&str[0], &str[1], &str[2]);
	return (len);
}

int			list_len(t_line *list)
{
	int		i;

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
	int			i;
	t_line		*tmp;

	i = 0;
	if (!list)
		return ;
	while (list->prev)
		list = list->prev;
	while (list)
	{
		if (list->next)
		{
			tmp = list->next;
			tmp->prev = list;
		}
		list->nb = i++;
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
