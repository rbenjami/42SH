/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:25:47 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/04 14:54:28 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_check_prio(char *v)
{
	if (!ft_strcmp(v, "|") || !ft_strcmp(v, "<") || !ft_strcmp(v, ">") || !ft_strcmp(v, ">>"))
		return (1);
	if (!ft_strcmp(v, "&&") || !ft_strcmp(v, "||"))
		return (2);
	if (!ft_strcmp(v, ";") || !ft_strcmp(v, "&"))
		return (3);
	return (-1);
}

void		add_token(t_token **token, char *value, enum e_token type)
{
	t_token		*new_token;
	t_token		*tmp;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->type = type;
	if (type == OPERATOR)
		new_token->prio = ft_check_prio(value);
	else
		new_token->prio = 0;
	if (!*token)
		*token = new_token;
	else
	{
		tmp = *token;
		while ((*token)->next)
			*token = (*token)->next;
		(*token)->next = new_token;
		*token = tmp;
	}
}
