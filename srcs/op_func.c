/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 16:04:09 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/14 18:53:20 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

pid_t		op_redir_left(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("redir left");
	return (0);
}

pid_t		op_double_redir_left(t_ast *tree, int pfd_old[2])
{
	(void)tree;
	(void)pfd_old;
	ft_putendl("double redir left");
	return (0);
}
