/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:19:14 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/26 15:05:32 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "sh.h"

void	parse_line(char *line)
{
	open_check(line);
}

int		main(void)
{
	char	*line;

	while (1)
	{
		ft_putstr("~> ");
		get_next_line(1, &line);
		if (line[0] != '\0')
			parse_line(line);
		free(line);
	}
	return (0);
}
