/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:19:14 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/26 14:44:54 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "sh.h"

int		main(void)
{
	char	*line;

	while (1)
	{
		ft_putstr("~> ");
		get_next_line(1, &line);
		if (line[0] != '\0')
			ft_putendl(line);
		free(line);
	}
	return (0);
}
