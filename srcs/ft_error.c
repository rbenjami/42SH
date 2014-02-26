/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:40:44 by dsousa            #+#    #+#             */
/*   Updated: 2014/02/26 16:14:21 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "sh.h"

/*
** pour ajouter une erreur : ajoutez une erreur.
*/

int		ft_error(int error_num, char *name, int program_end)
{
	static char		*tbl[2] =
	{
		": No such file or directory",
		": No read right"
	};

	ft_putstr_fd(name, 2);
	ft_putendl_fd(tbl[error_num], 2);
	if (program_end == TRUE)
		exit(0);
	return (-1);
}
