/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:33:23 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/26 18:01:24 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		redir_read2(t_ast *tree, int *fd, char **line)
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

int		redir_read(t_ast *tree, int *fd, int pfd_new[2])
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
	while (redir_read2(tree, fd, &line) > 0)
	{
		ft_putendl_fd(line, pfd_new[1]);
		ft_strdel(&line);
	}
	handler.len = 0;
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

pid_t	ft_redir(t_ast *tree, int pfd_old[2], int pfd_new[2], int pfd[2])
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

pid_t	op_redir(t_ast *t, int pfd_old[2])
{
	int		pfd[2];
	int		pfd_new[2];
	int		pid;

	pfd[0] = -1;
	pfd[1] = -1;
	if (!t->tk->redir)
		return (error("Parse error near `\\n'\n"));
	if (pipe(pfd_new) == -1)
		return (-42);
	pid = ft_redir(t, pfd_old, pfd_new, pfd);
	if (pid == -1)
		return (error("No such file or directory : %s\n", t->tk->redir->name));
	if (pfd_old)
		close_pfd(pfd_old);
	close_pfd(pfd);
	close_pfd(pfd_new);
	return (pid);
}
