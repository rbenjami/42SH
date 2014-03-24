/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:33:23 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/24 15:12:57 by killer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		redir_read(t_ast *tree, int *fd, int pfd_new[2])
{
	char	*line;

	if (tree->tk->redir->flag == OP_2REDIR_L)
		*fd = 0;
	else
		*fd =  open(tree->tk->redir->name, tree->tk->redir->flag, 00644);
	if (*fd == -1)
		return (-1);
	if (*fd == 0)
		ft_putstr("\033[31mheredoc> \033[m");
	while (get_next_line(*fd, &line) > 0)
	{
		if (*fd == 0)
		{
			if (ft_strcmp(line, tree->tk->redir->name) == 0)
			{
				ft_strdel(&line);
				break ;
			}
			ft_putstr("\033[31mheredoc> \033[m");
		}
		ft_putendl_fd(line, pfd_new[1]);
		ft_strdel(&line);
	}
	return (1);
}

int		ft_fill_redir(t_ast *tree, int *fd, int pfd_new[2], int pfd[2])
{
	int	b;

	b = 0;
	while (tree->tk->redir)
	{
		if (tree->tk->redir->flag == O_RDONLY 
			|| tree->tk->redir->flag == OP_2REDIR_L)
		{
			if (*fd > 2)
				close(*fd);
			if (redir_read(tree, fd, pfd_new) == -1)
				return (-1);
		}
		else
		{
			b = 1;
			if (pfd[1] > 2)
				close(pfd[1]);
			pfd[1] = open(tree->tk->redir->name, tree->tk->redir->flag, 00644);
		}
		tree->tk->redir = tree->tk->redir->next;
	}
	return (b);
}

pid_t		ft_redir(t_ast *tree, int pfd_old[2], int pfd_new[2], int pfd[2])
{
	int		fd;
	int		b;
	
	fd = -1;
	b = ft_fill_redir(tree, &fd, pfd_new, pfd);
	if (b == -1)
		return (-1);
	if (b && fd > -1)
	{
		if (!pfd_old) 
		 	pfd_old = pfd_new;
		pfd_old[0] = pfd_new[0];
	}
	else if (fd > -1)
	{
		pfd[0] = pfd_new[0];
		pfd[1] = pfd_new[1];
	}
	if (tree->left)
		return (execute(tree->left->tk->value, pfd_old, pfd, b));
	return (execute(ft_strdup("cat"), pfd_old, pfd, b));
}

pid_t		op_redir(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	int		pfd_new[2];
	int		pid;

	pfd[0] = -1;
	pfd[1] = -1;
	if (!tree->tk->redir)
		return (error("42sh: parse error near `\\n'\n"));
	if (pipe(pfd_new) == -1)
		return (-42);
	pid = ft_redir(tree, pfd_old, pfd_new, pfd);
	if (pid == -1)
		return (error("42sh: no such file or directory : %s\n", tree->tk->redir->name));
	if (pfd_old)
		close_pfd(pfd_old);
	close_pfd(pfd);
	close_pfd(pfd_new);
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
	if (ind == OP_REDIR_L)
		return (O_RDONLY);
	return (OP_2REDIR_L);
}

void	ft_modify_token_for_redir(t_token **token)
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
//			ft_modify_cmd(token, tmp, redir, cmd);
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
			if (!tmp)
			{
				error("42sh: parse error near `\\n'\n");
				return ;
			}
		}
		tmp = tmp->next;
	}
}
