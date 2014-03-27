/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:12:54 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/27 16:03:24 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_ind_op(char *v)
{
	if (!ft_strcmp(v, ">"))
		return (OP_REDIR_R);
	if (!ft_strcmp(v, "<"))
		return (OP_REDIR_L);
	if (!ft_strcmp(v, ">>"))
		return (OP_2REDIR_R);
	if (!ft_strcmp(v, "<<"))
		return (OP_2REDIR_L);
	if (!ft_strcmp(v, "|"))
		return (OP_PIPE);
	if (!ft_strcmp(v, "&&"))
		return (OP_AND);
	if (!ft_strcmp(v, "||"))
		return (OP_OR);
	if (!ft_strcmp(v, ";"))
		return (OP_SEMI_COL);
	if (!ft_strcmp(v, "&"))
		return (OP_BIN_AND);
	return (-1);
}

void	init_op(t_op_func **tab_op)
{
	*tab_op = (t_op_func *)ft_memalloc(sizeof(t_op_func) * 9);
	(*tab_op)[0] = &op_redir;
	(*tab_op)[1] = &op_redir;
	(*tab_op)[2] = &op_redir;
	(*tab_op)[3] = &op_redir;
	(*tab_op)[4] = &op_pipe;
	(*tab_op)[5] = &op_and;
	(*tab_op)[6] = &op_or;
	(*tab_op)[7] = &op_semi_col;
	(*tab_op)[8] = &op_bin_and;
}
