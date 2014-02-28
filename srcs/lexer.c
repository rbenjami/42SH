/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:41:06 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/28 14:59:24 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			collect_string(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (!is_operator(line[i]))
		i++;
	add_token(token, ft_strsub(line, 0, i), STRING);
	return (i - 1);
}

int			collect_operator(t_token **token, char *line)
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
	int		i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_operator(line[i]))
		i += collect_operator(token, &line[i]);
	else if (line[i] != '\0')
		i += collect_string(token, &line[i]);
	if (line[i] != '\0')
		lexer(token, &line[++i]);
}
