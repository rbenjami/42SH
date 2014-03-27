/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 10:09:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 13:27:48 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh.h"

void			save_hist(t_hist *hist, char *line, int new, t_ctrl_h *ctrl)
{
	t_hist		*new_elem;

	new_elem = malloc(sizeof(*new_elem));
	while (hist->next != NULL)
		hist = hist->next;
	new_elem->prev = hist;
	new_elem->next = NULL;
	new_elem->data = ft_strdup(line);
	hist->next = new_elem;
	hist->next->new = new;
	ctrl->last = new_elem;
}

t_ctrl_h		*new_hist(t_ctrl_h **ctrl)
{
	if (!((*ctrl)->start = ft_memalloc(sizeof(t_hist))))
		return (NULL);
	(*ctrl)->start->next = NULL;
	(*ctrl)->start->prev = NULL;
	(*ctrl)->start->new = -1;
	(*ctrl)->last = (*ctrl)->start;
	(*ctrl)->nb = 0;
	return ((*ctrl));
}
void			create_hist_else(t_ctrl_h *ctrl, int fd)
{
	ctrl->start->data = ft_strdup("./42SH");
	close(fd);
}

void			create_hist(t_ctrl_h *ctrl)
{
	char		*src;
	char		*line;
	char		*tmp;
	int			fd;

	tmp = ft_getenv("HOME");
	ctrl = new_hist(&ctrl);
	src = ft_strjoin(tmp, "/.42sh_history");
	fd = open(src, O_CREAT | O_RDONLY, 0777);
	free(tmp);
	free(src);
	if (get_next_line(fd, &line) > 0)
		ctrl->start->data = ft_strdup(line);
	else
		return (create_hist_else(ctrl, fd));
	if (line)
		free(line);
	while (get_next_line(fd, &line) > 0)
	{
		save_hist(ctrl->start, line, -1, ctrl);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
}
