/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:36:46 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/27 18:50:32 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_fill_redir2(t_ast *tree, int *fd, int pfd_new[2], int pfd[2])
{
	int		b;
	t_redir	*tmp;

	b = 0;
	tmp = tree->tk->redir;
	while (tmp)
	{
		if (tmp->flag == O_RDONLY || tmp->flag == OP_2REDIR_L)
		{
			b = 1;
			if (*fd > 2)
				close(*fd);
			if (redir_read(tree, fd, pfd_new) == -1)
				return (-1);
		}
		else
		{
			if (pfd[1] > 2)
				close(pfd[1]);
			pfd[1] = open(tmp->name, tmp->flag, 00644);
		}
		tmp = tmp->next;
	}
	return (b);
}

pid_t	ft_redir2(t_ast *tree, int pfd_old[2], int pfd_new[2], int pfd[2])
{
	int		fd;
	int		b;

	fd = -1;
	b = ft_fill_redir2(tree, &fd, pfd_new, pfd);
	if (b == -1)
		return (-1);
	if (b)
		pfd_old = pfd_new;
	if (tree->left)
		return (execute(tree->left->tk->value, pfd_old, pfd, 1));
	return (execute(ft_strdup("cat"), pfd_old, pfd, 1));
}

pid_t	op_redir2(t_ast *tree, int pfd_old[2], int pfd[2])
{
	int		pfd_new[2];
	int		pid;

	if (pipe(pfd_new) == -1)
		return (-42);
	if (!tree->tk->redir)
		return (error("parse error near `\\n'\n"));
	pid = ft_redir2(tree, pfd_old, pfd_new, pfd);
	if (pid == -1)
		return (error(NSF_ERROR, tree->tk->redir->name));
	close_pfd(pfd_new);
	return (pid);
}
