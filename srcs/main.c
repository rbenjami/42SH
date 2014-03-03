/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/03 17:18:08 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			collect_string(t_token **token, char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] && !is_operator(line[i]))
		i++;
	str = ft_strsub(line, 0, i);
	add_token(token, str, STRING);
	ft_strdel(&str);
	return (i - 1);
}

int			collect_operator(t_token **token, char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (is_operator(line[i]))
		i++;
	str = ft_strsub(line, 0, i);
	add_token(token, str, OPERATOR);
	ft_strdel(&str);
	return (i - 1);
}
void		lexer(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_operator(line[i]))
		i += collect_operator(token, &line[i]);
	else if (line[i] != '\0')
		i += collect_string(token, &line[i]);
	if (line[i] != '\0' && line[i + 1] != '\0')
		lexer(token, &line[++i]);
}

///////////////////	DEBUG !

char* tab_type[2] =
{
	"STRING",
	"OPERATOR"
};

void	DEBUG(t_token *token)
{
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
}
///////////////////	DEBUG !

void	free_token(t_token **token)
{
	t_token		*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		ft_strdel(&tmp->value);
		ft_memdel((void **)&tmp);
	}
}

int		main(void)
{
	char		*line;
	t_token		*token;

	token = NULL;
	while (1)
	{
		ft_putstr("~> ");
		get_next_line(0, &line);
		lexer(&token, line);
		free(line);
		DEBUG(token);
		free_token(&token);
	}
	return (0);
}
