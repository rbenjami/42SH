/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:23:36 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/02 17:12:28 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include "sh.h"

void			save_hist(t_hist *hist, char *line, int new, t_ctrl_h *ctrl)
{
	t_hist		*new_elem;

	new_elem = malloc(sizeof *new_elem);
	while (hist->next != NULL)
		hist = hist->next;
	new_elem->prev = hist;
	new_elem->next = NULL;
	new_elem->data = ft_strdup(line);
	new_elem->new = new;
	hist->next = new_elem;
	ctrl->last = new_elem;
}

/*
** add HISTFILE with setenv
** write history in .42sh_history with the builtin exit
*/

void			creat_hist(t_ctrl_h *ctrl)
{
	char		*src;
	int			fd;
	char		*line;

	ctrl->start->next = NULL;
	ctrl->start->prev = NULL;
	ctrl->start->new = 0;
	ctrl->last = ctrl->start;
	src = ft_strjoin(ft_getenv("HOME"), "/.42sh_history");
	fd = open(src, O_CREAT | O_RDWR);
	if (get_next_line(fd, &line) > 0)
		ctrl->start->data = ft_strdup(line);
	else
	{
		ctrl->start->data = ft_strdup("./42SH");
		return ;
	}
	while (get_next_line(fd, &line) > 0)
	{
		save_hist(ctrl->start, line, 0, ctrl);
		free(line);
	}
}
