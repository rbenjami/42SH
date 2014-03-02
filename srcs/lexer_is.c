/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 19:04:14 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/02 18:52:04 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ';' || c == '&')
		return (1);
	return (0);
}

int		is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int		is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int		is_alpha(char c)
{
	if (ft_isprint(c) && c != ' ' && !is_operator(c) && !is_quote(c))
		return (1);
	return (0);
}
