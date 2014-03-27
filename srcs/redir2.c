/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:36:46 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/27 12:38:14 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		redir_read222(t_ast *tree, int *fd, char **line)
{
	if (*fd == 0)
	{
		*line = reader(*fd, handler.hist);
		if (*line && ft_strcmp(*line, tree->tk->redir->name) == 0)
		{
			ft_strdel(line);
			return (0);
		}
		ft_putstr("\033[31mheredoc> \033[m");
		return (1);
	}
	return (get_next_line(*fd, line));
}

int		redir_read22(t_ast *tree, int *fd, int pfd_new[2])
{
	char	*line;

	if (tree->tk->redir->flag == OP_2REDIR_L)
	{
		*fd = 0;
		handler.len = 9;
	}
	else
		*fd = open(tree->tk->redir->name, tree->tk->redir->flag, 00644);
	if (*fd == -1)
		return (-1);
	if (*fd == 0)
		ft_putstr("\033[31mheredoc> \033[m");
	while (redir_read222(tree, fd, &line) > 0)
	{
		ft_putendl_fd(line, pfd_new[1]);
		ft_strdel(&line);
	}
	handler.len = 0;
	return (1);
}

int		ft_fill_redir2(t_ast *tree, int *fd, int pfd_new[2], int pfd[2])
{
	int	b;

	b = 0;
	while (tree->tk->redir)
	{
		if (tree->tk->redir->flag == O_RDONLY
			|| tree->tk->redir->flag == OP_2REDIR_L)
		{
			b = 1;
			if (*fd > 2)
				close(*fd);
			if (redir_read22(tree, fd, pfd_new) == -1)
				return (-1);
		}
		else
		{
			if (pfd[1] > 2)
				close(pfd[1]);
			pfd[1] = open(tree->tk->redir->name, tree->tk->redir->flag, 00644);
		}
		tree->tk->redir = tree->tk->redir->next;
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
		return (error("Parse error near `\\n'\n"));
	pid = ft_redir2(tree, pfd_old, pfd_new, pfd);
	if (pid == -1)
		return (error(NSF_ERROR, tree->tk->redir->name));
	close_pfd(pfd_new);
	return (pid);
}
