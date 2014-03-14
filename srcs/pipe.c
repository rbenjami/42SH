/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:46:49 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 18:46:55 by rbenjami         ###   ########.fr       */
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
			execute(tree->left->tk->value, pfd_old, pfd, 1);
			if (pfd_old)
				close_pfd(pfd_old);
			if (tree->right && tree->right->tk->prio > 0)
				resolve_tree(tree->right, pfd);
			else
				op_pipe2(tree, pfd, &pid);
		}
		else
			error("parse error near `|'", NULL);
	}
	return (pid);
}
