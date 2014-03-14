/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolored_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 22:48:27 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 22:51:09 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putcolored_str(char *str, int color)
{
	if (color == BLACK)
		ft_putstr("\033[30m");
	if (color == RED)
		ft_putstr("\033[31m");
	if (color == GREEN)
		ft_putstr("\033[32m");
	if (color == YELLOW)
		ft_putstr("\033[33m");
	if (color == BLUE)
		ft_putstr("\033[34m");
	if (color == MAGENTA)
		ft_putstr("\033[35m");
	if (color == CYAN)
		ft_putstr("\033[36m");
	if (color == WITHE)
		ft_putstr("\033[37m");
	ft_putstr(str);
	ft_putstr("\033[m");
	return (1);
}
