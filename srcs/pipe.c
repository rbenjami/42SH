/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killer <killer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:46:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/22 17:21:08 by killer           ###   ########.fr       */
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
		ft_putstr("\033[31mpipe> \033[m");
		get_next_line(0, &line);
		*pid = execute(line, NULL, pfd, 0);
		ft_strdel(&line);
	}
	close_pfd(pfd);
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
			if (tree->left->tk->prio != 1)
				execute(tree->left->tk->value, pfd_old, pfd, 1);
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
