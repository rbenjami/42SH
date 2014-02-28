/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 17:05:36 by dsousa            #+#    #+#             */
/*   Updated: 2014/02/28 17:51:05 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "sh.h"

void			builtin_history_c(t_hist *hist)
{
	int		nb;

	nb = 0;
	hist = hist->start;
	ft_putendl("\033[32mCurrent shell commands history:\033[0m");
	while (hist)
	{
		if (hist->new)
		{
			write(1, " ", 1);
			ft_putnbr(nb);
			write(1, "  ", 2);
			ft_putendl(hist->data);
		}
		nb++;
		hist = hist->next;
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

void			builtin_history(t_hist *hist)
{
	int		nb;
	int		nb_elem;

	nb = 0;
	nb_elem = ft_len_list(hist->start);
	hist = hist->last;
	ft_putendl("\033[32mLast shell commands history:\033[0m");
	while (hist && nb <= 15)
	{
		write(1, " ", 1);
		ft_putnbr(nb_elem - nb);
		write(1, "  ", 2);
		ft_putendl(hist->data);
		nb++;
		hist = hist->prev;
	}
}
