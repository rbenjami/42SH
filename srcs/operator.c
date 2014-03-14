/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 18:53:29 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 18:53:41 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

pid_t		op_and(t_ast *tree, int pfd_old[2])
{
	resolve_tree(tree->left, pfd_old);
	if (handler.cmd == 0)
		resolve_tree(tree->right, pfd_old);
	return (0);
}

pid_t		op_or(t_ast *tree, int pfd_old[2])
{
	resolve_tree(tree->left, pfd_old);
	if (handler.cmd != 0)
		resolve_tree(tree->right, pfd_old);
	return (0);
}

pid_t		op_semi_col(t_ast *tree, int pfd_old[2])
{
	resolve_tree(tree->left, pfd_old);
	resolve_tree(tree->right, pfd_old);
	return (0);
}

pid_t		op_bin_and(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("bin and");
	return (0);
}
