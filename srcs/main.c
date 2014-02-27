/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:19:14 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 15:02:21 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "sh.h"

void	parse_line(char *line)
{
	t_word	*word;
	//open_check(line);
	word = ft_lexer(line);
	while (word)
	{
		ft_putnbr(word->type);
		ft_putendl(word->word);
		word = word->next;
	}
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
