/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 10:09:20 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/26 19:19:33 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
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
	new_elem->new = new;
	hist->next = new_elem;
	ctrl->last = new_elem;
}

t_ctrl_h		*new_hist(t_ctrl_h **ctrl)
{
	if (!((*ctrl)->start = ft_memalloc(sizeof(t_hist))))
		return (NULL);
	(*ctrl)->start->next = NULL;
	(*ctrl)->start->prev = NULL;
	(*ctrl)->start->new = 0;
	(*ctrl)->last = (*ctrl)->start;
	(*ctrl)->nb = 0;
	return ((*ctrl));
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
	{
		ctrl->start->data = ft_strdup("./42SH");
		close(fd);
		return ;
	}
	while (get_next_line(fd, &line) > 0)
	{
		save_hist(ctrl->start, line, 0, ctrl);
		free(line);
	}
	close(fd);
}
