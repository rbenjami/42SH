/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:46:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/27 01:46:22 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		op_pipe2(t_ast *tree, int pfd[2], int *pid)
{
	char		*line;

	if (tree->right)
		*pid = execute(tree->right->tk->value, NULL, pfd, 0);
	else
	{
		handler.len = 6;
		ft_putstr("\033[31mpipe> \033[m");
		line = reader(0, handler.hist);
		*pid = execute(line, NULL, pfd, 0);
		ft_strdel(&line);
		handler.len = 0;
	}
	close_pfd(pfd);
}

void		ft_redir_pipe(t_ast *tree, int pfd_old[2], int pfd[2])
{
	int			pid;
	int			status;

	pid = op_redir2(tree->left, pfd_old, pfd);
	waitpid(pid, &status, 0);
	handler.cmd = WEXITSTATUS(status);
}
pid_t		op_pipe(t_ast *tree, int pfd_old[2])
{
	int			pfd[2];
	pid_t		pid;

	pid = 0;
	if (pipe(pfd) != -1)
	{
		if (tree->left)
		{
			if (tree->left->tk->prio == 1)
				ft_redir_pipe(tree, pfd_old, pfd);
			else
				pid = execute(tree->left->tk->value, pfd_old, pfd, 1);
			if (pfd_old)
				close_pfd(pfd_old);
			if (tree->right && tree->right->tk->prio > 0)
				resolve_tree(tree->right, pfd);
			else
				op_pipe2(tree, pfd, &pid);
		}
		else
			error("42sh: parse error near `|'\n");
	}
	return (pid);
}
