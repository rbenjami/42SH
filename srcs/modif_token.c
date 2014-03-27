/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:43:57 by killer            #+#    #+#             */
/*   Updated: 2014/03/27 12:58:23 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		flag_op(int ind)
{
	if (ind == OP_REDIR_R)
		return (OPEN_REDIR_R);
	if (ind == OP_2REDIR_R)
		return (OPEN_2REDIR_R);
	if (ind == OP_REDIR_L)
		return (O_RDONLY);
	return (OP_2REDIR_L);
}

int		ft_modify_cmd2(t_token **token, t_token **tmp, int *flag)
{
	int		ind;

	if (!*tmp)
		return (1);
	ind = ft_ind_op((*tmp)->value);
	if (ind >= 0 && ind <= 3)
	{
		*flag = flag_op(ind);
		ft_lstremove_redir(token, tmp);
	}
	return (0);
}

int		ft_mod_cmd(t_token **tk, t_token **tmp, t_token **cmd, t_token **redir)
{
	char	**tab;
	int		flag;
	int		i;

	flag = flag_op(ft_ind_op((*redir)->value));
	while (*tmp && (*tmp)->prio == 0)
	{
		i = 1;
		tab = ft_strsplit_space((*tmp)->value);
		if (!*cmd && tab[1])
			*cmd = append_token(tk, redir);
		while (tab[i])
		{
			ft_strjoin2(&(*cmd)->value, " ");
			ft_strjoin2(&(*cmd)->value, tab[i++]);
		}
		ft_lstadd_redir(*redir, tab[0], flag);
		ft_free_tab(&tab);
		ft_lstremove_redir(tk, tmp);
		if (ft_modify_cmd2(tk, tmp, &flag) == 1)
			return (1);
	}
	return (0);
}

int		ft_modify_token_for_redir(t_token **token)
{
	int		ind;
	t_token	*t[3];

	t[0] = *token;
	t[1] = NULL;
	t[2] = NULL;
	while (t[0])
	{
		if ((ind = ft_ind_op(t[0]->value)) >= 0 && ind <= 3)
		{
			t[1] = t[0]->prev;
			t[2] = t[0];
		}
		else if (t[2] && (ind = ft_ind_op((t[2])->value)) >= 0 && ind <= 3)
		{
			if (ft_mod_cmd(token, t + 0, t + 1, t + 2) == 1)
				return (0);
			if (!t[0])
				return (error("42sh: parse error near `\\n'\n"));
			t[2] = NULL;
			t[1] = NULL;
		}
		t[0] = t[0]->next;
	}
	return (0);
}
