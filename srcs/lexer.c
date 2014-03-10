/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 13:45:05 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/10 13:46:38 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			collect_string(t_token **token, char *line)
{
	int		i;
	char	*str;
	int		quote;
	char	q;

	i = 0;
	quote = 0;
	q = 0;
	while (line[i] && (!is_operator(line[i]) || quote))
	{
		if (line[i] == '\\')
			i++;
		if (is_quote(line[i]) && (line[i] == q || q == 0))
		{
			q = line[i];
			quote = !quote;
		}
		i++;
	}
	str = ft_strsub(line, 0, i);
	if (str[0])
	{
		add_token(token, str, STRING);
		ft_strdel(&str);
	}
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
	if (str[0])
	{
		add_token(token, str, OPERATOR);
		ft_strdel(&str);
	}
	return (i - 1);
}

void		lexer(t_token **token, char *line)
{
	int		i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == '\\')
		i++;
	else if (is_operator(line[i]))
		i += collect_operator(token, &line[i]);
	else if (line[i] != '\0')
		i += collect_string(token, &line[i]);
	if (line[i] != '\0' && line[i + 1] != '\0')
		lexer(token, &line[++i]);
}
