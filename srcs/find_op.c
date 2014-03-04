/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:12:54 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/04 17:22:03 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_ind_op(char *v)
{
	if (!ft_strcmp(v, ">"))
		return (0);
	if (!ft_strcmp(v, "<"))
		return (1);
	if (!ft_strcmp(v, ">>"))
		return (2);
	if (!ft_strcmp(v, "<<"))
		return (3);
	if (!ft_strcmp(v, "|"))
		return (4);
	if (!ft_strcmp(v, "&&"))
		return (5);
	if (!ft_strcmp(v, "||"))
		return (6);
	if (!ft_strcmp(v, ";"))
		return (7);
	if (!ft_strcmp(v, "&"))
		return (8);
	return (-1);
}

void	init_op(op_func **tab_op)
{
	*tab_op = (op_func *)ft_memalloc(sizeof(op_func) * 9);
	(*tab_op)[0] = &op_redir_right;
	(*tab_op)[1] = &op_redir_left;
	(*tab_op)[2] = &op_double_redir_right;
	(*tab_op)[3] = &op_double_redir_left;
	(*tab_op)[4] = &op_pipe;
	(*tab_op)[5] = &op_and;
	(*tab_op)[6] = &op_or;
	(*tab_op)[7] = &op_semi_col;
	(*tab_op)[8] = &op_bin_and;
}
