/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:25:47 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/03 17:12:43 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
