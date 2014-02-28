/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:23:36 by dsousa            #+#    #+#             */
/*   Updated: 2014/02/28 17:05:17 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include "sh.h"

static void		last_hist(t_hist *last, t_hist *hist)
{
	while (hist->next)
	{
		hist->last = last;
		hist = hist->next;
	}
}

void			save_hist(t_hist *hist, char *line, int new)
{
	t_hist		*new_elem;

	new_elem = malloc(sizeof *new_elem);
	new_elem->start = hist;
	new_elem->last = new_elem;
	while (hist->next != NULL)
		hist = hist->next;
	new_elem->prev = hist;
	new_elem->next = NULL;
	new_elem->data = ft_strdup(line);
	new_elem->new = new;
	hist->next = new_elem;
	hist = hist->start;
	while (hist->next)
		hist = hist->next;
	last_hist(hist, hist->start);
}

/*
** add HISTFILE with setenv
** write history in .42sh_history in the builtin exit
*/

void			creat_hist(t_hist *hist)
{
	char		*src;
	int			fd;
	char		*line;

	hist->next = NULL;
	hist->prev = NULL;
	hist->start = hist;
	hist->new = 0;
	hist->last = hist;
	src = ft_strjoin(ft_getenv("HOME"), "/.42sh_history");
	fd = open(src, O_CREAT | O_RDWR);
	if (get_next_line(fd, &line) > 0)
		hist->data = ft_strdup(line);
	else
	{
		hist->data = ft_strdup("./42SH");
		return ;
	}
	while (get_next_line(fd, &line) > 0)
	{
		save_hist(hist->start, line, 0);
		free(line);
	}
}
