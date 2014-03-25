/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:48:15 by killer            #+#    #+#             */
/*   Updated: 2014/03/24 19:48:29 by killer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_lstadd_redir(t_token *token, char *name, int flag)
{
	t_redir	*tmp;
	t_redir	*new_redir;

	new_redir = (t_redir *)ft_memalloc(sizeof(t_redir));
	if (new_redir)
	{
		new_redir->name = ft_strdup(name);
		new_redir->flag = flag;
		new_redir->next = NULL;
		if (!token->redir)
			token->redir = new_redir;
		else
		{
			tmp = token->redir;
			while (token->redir->next)
				token->redir = token->redir->next;
			token->redir->next = new_redir;
			token->redir = tmp;
		}
	}
}

void	ft_lstremove_redir(t_token **token, t_token **remove)
{
	t_token	*tmp;

	tmp = *remove;
	if (*remove)
	{
		if ((*remove)->prev)
		{
			if ((*remove)->next)
				(*remove)->next->prev = (*remove)->prev;
			(*remove)->prev->next = (*remove)->next;
		}
		else
			*token = (*remove)->next;
		*remove = (*remove)->next;
		free_token(&tmp);
	}
}
