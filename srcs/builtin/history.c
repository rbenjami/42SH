/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 15:32:10 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 15:37:33 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "sh.h"

static void		builtin_history_c(t_hist *hist)
{
	int		nb;

	nb = 0;
	ft_putendl("\033[32mCurrent shell commands history:\033[0m");
	while (hist)
	{
		if (hist->new != -1)
		{
			write(1, " ", 1);
			ft_putnbr(nb);
			write(1, "  ", 2);
			ft_putendl(hist->data);
			nb++;
		}
		hist = hist->prev;
	}
}

static int		ft_len_list(t_hist *hist)
{
	int		i;

	i = 0;
	while (hist)
	{
		i++;
		hist = hist->next;
	}
	return (i);
}

int				builtin_history(char **av)
{
	int		nb;
	int		nb_elem;
	t_hist	*h;

	nb = 0;
	h = g_handler.hist->last;
	if (av[1] && !ft_strcmp(av[1], "-c"))
	{
		builtin_history_c(g_handler.hist->last);
		return (0);
	}
	nb_elem = ft_len_list(g_handler.hist->start);
	ft_putendl("\033[32mLast shell commands history:\033[0m");
	while (h && nb <= 15)
	{
		write(1, " ", 1);
		ft_putnbr(nb_elem - nb);
		write(1, "  ", 2);
		ft_putendl(h->data);
		nb++;
		h = h->prev;
	}
	return (0);
}
