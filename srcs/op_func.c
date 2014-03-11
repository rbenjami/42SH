/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:04:09 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/11 18:25:11 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		close_pfd(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

pid_t		op_redir_right(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	int		pid;

	pid = 0;
	if (tree->right)
	{
		pfd[0] = -1;
		if (tree->right && tree->right->tk->prio == 0)
			pfd[1] = open(tree->right->tk->value, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		pid = execute(tree->left->tk->value, pfd_old, pfd, 1);
		if (pfd_old)
			close_pfd(pfd_old);
		waitpid(pid, 0, 0);
		close(pfd[1]);
	}
	return (pid);
}

pid_t		op_redir_left(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("redir left");
	return(0);
}

pid_t		op_double_redir_right(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	int		pid;

	pid = 0;
	if (tree->right)
	{
		pfd[0] = -1;
		if (tree->right && tree->right->tk->prio == 0)
			pfd[1] = open(tree->right->tk->value, O_WRONLY | O_CREAT | O_APPEND, 00644);
		pid = execute(tree->left->tk->value, pfd_old, pfd, 1);
		if (pfd_old)
			close_pfd(pfd_old);
		waitpid(pid, 0, 0);
		close(pfd[1]);
	}
	return (pid);
}

pid_t		op_double_redir_left(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("double redir left");
	return(0);
}

pid_t		op_pipe(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	pid_t		pid;
	char		*line;

	pid = 0;
	if (pipe(pfd) != -1)
	{
		if (tree->left)
		{
			execute(tree->left->tk->value, pfd_old, pfd, 1);
			if (pfd_old)
				close_pfd(pfd_old);
			if (tree->right && tree->right->tk->prio > 0)
				resolve_tree(tree->right, pfd);
			else
			{
				if (tree->right)
					pid = execute(tree->right->tk->value, NULL, pfd, 0);
				else
				{
					ft_putstr("pipe> ");
					get_next_line(0, &line);
					pid = execute(line, NULL, pfd, 0);
					ft_strdel(&line);
				}
				close_pfd(pfd);
			}
			waitpid(pid, 0, 0);
		}
		else
			error("parse error near `|'", NULL);
	}
	return (pid);
}

pid_t		op_and(t_ast *tree, int pfd_old[2])
{
	resolve_tree(tree->left, pfd_old);
	if (handler.cmd == 0)
		resolve_tree(tree->right, pfd_old);
	return(0);
}

pid_t		op_or(t_ast *tree, int pfd_old[2])
{
	resolve_tree(tree->left, pfd_old);
	if (handler.cmd != 0)
		resolve_tree(tree->right, pfd_old);
	return(0);
}

pid_t		op_semi_col(t_ast *tree, int pfd_old[2])
{
	resolve_tree(tree->left, pfd_old);
	resolve_tree(tree->right, pfd_old);
	return(0);
}

pid_t		op_bin_and(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("bin and");
	return(0);
}

