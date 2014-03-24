/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:25:47 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/16 13:43:53 by killer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_check_prio(char *v)
{
	if ( !ft_strcmp(v, "<") || !ft_strcmp(v, ">") 
		|| !ft_strcmp(v, ">>") || !ft_strcmp(v, "<<"))
		return (1);
	if (!ft_strcmp(v, "|"))
		return (2);
	if (!ft_strcmp(v, "&&") || !ft_strcmp(v, "||"))
		return (3);
	if (!ft_strcmp(v, ";") || !ft_strcmp(v, "&"))
		return (4);
	return (-1);
}

void		add_token(t_token **token, char *value, enum e_token type)
{
	t_token		*new_token;
	t_token		*tmp;

	new_token = (t_token *)ft_memalloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->redir = NULL;
	new_token->type = type;
	new_token->prio = (type == OPERATOR) ? ft_check_prio(value) : 0;
	if (!*token)
		*token = new_token;
	else
	{
		tmp = *token;
		while ((*token)->next)
			*token = (*token)->next;
		new_token->prev = (*token);
		(*token)->next = new_token;
		*token = tmp;
	}
}

t_token		*ft_new_token()
{
	t_token	*new_token;

	new_token = (t_token *)ft_memalloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup("");
	new_token->prio = 0;
	new_token->type = 0;
	new_token->redir = NULL;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_token		*append_token(t_token **token, t_token **add)
{
	t_token	*new_token;

	if ((new_token = ft_new_token()) == NULL)
		return (NULL);
	if (*add)
	{
		if (!(*add)->prev)
		{
			new_token->next = *token;
			*token = new_token;
		}
		else
		{
			(*add)->prev->next = new_token;
			new_token->next = *add;
			new_token->prev = (*add)->prev;
			(*add)->prev = new_token;
		}
	}
	return (new_token);
}

void		free_token(t_token **token)
{
	if (*token)
	{
		free((*token)->value);
		(*token)->value = NULL;
		free(*token);
		*token = NULL;
	}
}
