/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:19:14 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 19:06:30 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "sh.h"

///////////////////	DEBUG !

char* tab_type[4] =
{
	"STRING",
	"DIGIT",
	"ALPHA",
	"OPERATOR"
};

///////////////////	DEBUG !

void	parse_line(char *line)
{
	t_token	*token;

	token = NULL;
	lexer(&token, line);
	//	DEBUG !
	while (token)
	{
		ft_putstr("\033[32mTYPE: \033[33m");
		ft_putstr(tab_type[token->type]);
		ft_putstr("\033[m : \033[31m");
		ft_putnbr(token->type);
		ft_putstr("\n\033[32mVALUE: \033[33m");
		ft_putendl(token->value);
		ft_putstr("\n\033[0m");
		token = token->next;
	}
	//	DEBUG !
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
