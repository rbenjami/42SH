/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 15:09:37 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 19:06:01 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		collect_string(t_token **token, char *line)
{
	char	end;
	int		i;

	i = 1;
	end = line[0];
	while (!(line[i] == end || line[i] == '\0'))
	{
		if (line[i] == '\\')
			i++;
		i++;
	}
	add_token(token, ft_strsub(line, 0, i + 1), STRING);
	return (i);
}

int		collect_alpha(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (is_alpha(line[i]) || ft_isdigit(line[i]))
		i++;
	add_token(token, ft_strsub(line, 0, i), ALPHA);
	return (i - 1);
}

int		collect_digit(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (is_alpha(line[i]))
		return (collect_alpha(token, line));
	add_token(token, ft_strsub(line, 0, i), DIGIT);
	return (i - 1);
}

int		collect_operator(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (is_operator(line[i]))
		i++;
	add_token(token, ft_strsub(line, 0, i), OPERATOR);
	return (i - 1);
}

void		lexer(t_token **token, char *line)
{
	int			i;
	int			op;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_quote(line[i]))
		i += collect_string(token, &line[i]);
	else if (ft_isdigit(line[i]))
		i += collect_digit(token, &line[i]);
	else if ((op = find_op(&line[i])) != -1)
		i += collect_operator(token, &line[i]);
	else if (is_alpha(line[i]))
		i += collect_alpha(token, &line[i]);
	if (line[i] != '\0')
		lexer(token, &line[++i]);
}
