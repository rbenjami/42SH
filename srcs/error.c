/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:26:15 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/04 16:39:54 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		error(const char *s1, char *s2)
{
	ft_putstr_fd("42sh: \033[31m", 2);
	if (!s2)
	{
		ft_putendl_fd(s1, 2);
		ft_putstr_fd("\033[m", 2);
	}
	else
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd("\033[m", 2);
		ft_putendl_fd(s2, 2);
	}
	return (-42);
}
