/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:01:26 by dsousa            #+#    #+#             */
/*   Updated: 2014/02/26 16:13:03 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "sh.h"

void	open_check(char *path)
{
	if (access(path, F_OK) == -1)
		ft_error(0, path, FALSE);
	else if (access(path, R_OK) == -1)
		ft_error(1, path, FALSE);
}
