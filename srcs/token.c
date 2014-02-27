/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 19:03:16 by rbenjami          #+#    #+#             */
/*   Updated: 2014/02/27 19:03:28 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		add_token(t_token **token, char *value, int type)
{
	t_token	*tmp;
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token)
	{
		new_token->value = value;
		new_token->type = type;
		new_token->next = NULL;
	}
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
