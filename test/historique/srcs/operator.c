/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 19:06:39 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 19:06:56 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			find_op(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (OP_REDIR_RIGHT2);
	if (str[0] == '<' && str[1] == '<')
		return (OP_REDIR_LEFT2);
	if (str[0] == '&' && str[1] == '&')
		return (OP_AND);
	if (str[0] == '|' && str[1] == '|')
		return (OP_OR);
	if (str[0] == '|')
		return (OP_PIPE);
	if (str[0] == '>')
		return (OP_REDIR_RIGHT);
	if (str[0] == '<')
		return (OP_REDIR_LEFT);
	if (str[0] == ';')
		return (OP_SEMICOLON);
	return (-1);
}
