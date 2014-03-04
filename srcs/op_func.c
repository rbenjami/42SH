/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:04:09 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/04 18:46:37 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		op_redir_right(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("redir right");
	return(0);
}

int		op_redir_left(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("redir left");
	return(0);
}

int		op_double_redir_right(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("double redir right");
	return(0);
}

int		op_double_redir_left(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("double redir left");
	return(0);
}

int		op_pipe(t_ast *left, t_ast *right)
{
	int			pfd[2];

	if (left && left->tk->prio > 0)
		resolve_tree(left);
	if (right && right->tk->prio > 0)
		resolve_tree(right);
	if (left && left->tk->prio == 0)
	{
		execute(left->tk->value);
	}
	if (right && right->tk->prio == 0)
		execute(right->tk->value);

	if (pipe(pfd) == -1)
		return (error("pipe error, ", NULL));
	ft_putendl("pipe");
	return(0);
}

int		op_and(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("and");
	return(0);
}

int		op_or(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("or");
	return(0);
}

int		op_semi_col(t_ast *left, t_ast *right)
{
	// if (left && left->tk->prio > 0)
	// 	resolve_tree(left);
	// if (right && right->tk->prio > 0)
	// 	resolve_tree(right);
	if (left && left->tk->prio == 0)
		execute(left->tk->value);
	if (right && right->tk->prio == 0)
		execute(right->tk->value);
	return(0);
}

int		op_bin_and(t_ast *left, t_ast *right)
{
	(void)left;
	(void)right;
	ft_putendl("bin and");
	return(0);
}

