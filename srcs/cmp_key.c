/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 17:11:08 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/17 13:12:06 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	delete_first(t_line *list)
{
	if (list->next)
	{
		list->data = list->next->data;
		list->next = list->next->next;
		list->prev = NULL;
		verif_nb(list);
	}
	else
		list->data = 0;
}

void	ft_down(char *key, int *cursor, t_line *list)
{
	if (key && *cursor && list)
		ft_putchar('0');
}

void	ft_up(char *key, int *cursor, t_line *list)
{
	if (key && *cursor && list)
		ft_putchar('0');
}

int		cmp_key(char *key, int *cursor, t_line *list)
{
	int				i;
	static t_key	tbl[7] =
	{
		{UP, &ft_up},
		{LEFT, &ft_left},
		{RIGHT, &ft_right},
		{DOWN, &ft_down},
		{DEL, &ft_del},
		{SUPR, &ft_supr},
		{0, 0}
	};

	i = 0;
	while (tbl[i].key)
	{
		if (*(unsigned int *)key == (unsigned int)tbl[i].key)
		{
			tbl[i].f(key, cursor, list);
			return (1);
		}
		i++;
	}
	return (0);
}
