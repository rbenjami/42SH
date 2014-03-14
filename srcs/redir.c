/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:33:23 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 18:43:11 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

pid_t		op_redir(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	int		pid;

	pid = 0;
	pfd[0] = -1;
	while (tree->tk->redir)
	{
		pfd[1] = open(tree->tk->redir->name, tree->tk->redir->flag, 00644);
		if (tree->tk->redir->next)
			close(pfd[1]);
		tree->tk->redir = tree->tk->redir->next;
	}
	if (tree->left)
		pid = execute(tree->left->tk->value, pfd_old, pfd, 1);
	else
		pid = execute(ft_strdup("cat"), pfd_old, pfd, 1);
	if (pfd_old)
		close_pfd(pfd_old);
	close(pfd[1]);
	return (pid);
}

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

int		flag_op(int ind)
{
	if (ind == OP_REDIR_R)
		return (OPEN_REDIR_R);
	if (ind == OP_2REDIR_R)
		return (OPEN_2REDIR_R);
	return (O_RDONLY);
}

void	ft_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*cmd;
	t_token	*redir;
	char	**tab;
	int		i;
	int		flag;
	int		ind;

	tmp = *token;
	cmd = NULL;
	redir = NULL;
	while (tmp)
	{
		ind = ft_ind_op(tmp->value);
		if (ind >= 0 && ind <= 3)
		{
			flag = flag_op(ind);
			cmd = tmp->prev;
			redir = tmp;
		}
		else if (tmp->prev && ft_ind_op(tmp->prev->value) >= 0 && ft_ind_op(tmp->prev->value) <= 3)
		{
			while (tmp)
			{
				tab = ft_strsplit_space(tmp->value);
				if (!cmd && tab[1])
					cmd = append_token(token, &redir);
				i = 1;
				while (tab[i])
				{
					ft_strjoin2(&cmd->value, " ");
					ft_strjoin2(&cmd->value, tab[i++]);
				}
				ft_lstadd_redir(redir, tab[0], flag);
				ft_free_tab(&tab);
				ft_lstremove_redir(token, &tmp);
				if (!tmp)
					return ;
				ind = ft_ind_op(tmp->value);
				if (ind >= 0 && ind <= 3)
				{
					flag = flag_op(ind);
					ft_lstremove_redir(token, &tmp);
				}
				else
					break ;
			}
		}
		tmp = tmp->next;
	}
}
