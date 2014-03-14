/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolored_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 22:46:16 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 22:50:57 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putcolored_char(char c, int color)
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
	ft_putchar(c);
	ft_putstr("\033[m");
	return (1);
}
