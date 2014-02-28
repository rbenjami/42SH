/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 13:19:14 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/28 17:49:02 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "sh.h"

///////////////////	DEBUG !

char* tab_type[5] =
{
	"STRING",
	"DIGIT",
	"ALPHA",
	"OPERATOR",
	"QUOTE"
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
	char		*line;
	t_hist		hist;

	creat_hist(&hist);
	while (1)
	{
		ft_putstr("~> ");
		get_next_line(1, &line);
		save_hist(hist.start, line, 1);
		if (ft_strcmp(line, "history -c") == 0)
			builtin_history_c(hist.start);
		else if (ft_strcmp(line, "history") == 0)
			builtin_history(hist.start);
		if (line[0] != '\0')
			parse_line(line);
		free(line);
	}
	return (0);
}
