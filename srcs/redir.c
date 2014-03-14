/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 12:28:26 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 12:49:04 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

pid_t		op_redir_right(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	pid_t	pid;

	pid = 0;
	if (tree->right)
	{
		pfd[0] = -1;
		if (tree->left && tree->right && tree->right->tk->prio == 0)
			pfd[1] = open(tree->right->tk->value, OPEN_REDIR_R, 00644);
		if (tree->left)
			pid = execute(tree->left->tk->value, pfd_old, pfd, 1);
		if (pfd_old)
			close_pfd(pfd_old);
		close(pfd[1]);
	}
	return (pid);
}

pid_t		op_redir_left(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("redir left");
	return (0);
}

pid_t		op_double_redir_right(t_ast *tree, int pfd_old[2])
{
	int		pfd[2];
	pid_t	pid;

	pid = 0;
	if (tree->right)
	{
		pfd[0] = -1;
		if (tree->right && tree->right->tk->prio == 0)
			pfd[1] = open(tree->right->tk->value, OPEN_2REDIR_R, 00644);
		pid = execute(tree->left->tk->value, pfd_old, pfd, 1);
		if (pfd_old)
			close_pfd(pfd_old);
		close(pfd[1]);
	}
	return (pid);
}

pid_t		op_double_redir_left(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("double redir left");
	return (0);
}
