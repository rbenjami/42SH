/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 16:15:22 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/21 15:50:25 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include "sh.h"

void			freelist(t_line *list)
{
	t_line *tmp;

	tmp = NULL;
	if (list)
		tmp = list->next;
	while ((list = tmp))
	{
		tmp = list->next;
		free(list);
	}
}

char			*create_line(t_line *list)
{
	int			len;
	char		*line;
	t_line		*tmp;

	tmp = list;
	if (!list->data)
	{
		line = ft_memalloc(sizeof(char *));
		line[0] = '\n';
		return (line);
	}
	len = list_len(list);
	line = ft_memalloc(sizeof(char) * (len + 1));
	len = 0;
	while (list)
	{
		line[len] = list->data;
		len++;
		list = list->next;
	}
	line[len] = '\0';
	freelist(tmp);
	return (line);
}

char			*reader(int fd)
{
	char		c[5];
	t_line		list;
	int			cursor;

	cursor = 0;
	ft_bzero(c, 5);
	list.data = 0;
	if (read(fd, c, 4) < 0)
		return (NULL);
	modif_list(&list, c, &cursor);
	if (ft_match(c, '\n'))
		cursor = -42;
	ft_bzero(c, 5);
	while (cursor != -42 && read(fd, c, 4) > 0)
	{
		if (ft_match(c, '\n'))
		{
			write(1, "\n", 1);
			break ;
		}
		modif_list(&list, c, &cursor);
		ft_bzero(c, 5);
	}
	return (create_line(&list));
}
