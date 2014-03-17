/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 17:11:08 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/17 12:32:24 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		cmp_key(char *key)
{
	static int		tbl[7] = {UP, LEFT, RIGHT, DOWN, DEL, SUPR, 0};
	int				i;
	i = 0;
	while (tbl[i])
	{
		if (*(unsigned int *)key == (unsigned int)tbl[i])
			return (1);
		i++;
	}
	return (0);
}
