/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:26:15 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/11 12:20:20 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		error(const char *s1, char *s2)
{
	ft_putstr_fd("42sh: \033[31m", ERR);
	if (!s2)
	{
		ft_putendl_fd(s1, ERR);
		ft_putstr_fd("\033[m", ERR);
	}
	else
	{
		ft_putstr_fd(s1, ERR);
		ft_putstr_fd("\033[m", ERR);
		ft_putendl_fd(s2, ERR);
	}
	return (-42);
}
