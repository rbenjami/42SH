/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:50:14 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/02 15:32:06 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
typedef struct 		s_ast
{
	t_token			*tk;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_ctrl
{
	t_ast			*ast_start;
	t_token			*tk_start;
	char			**env;
}					t_ctrl;

typedef struct		s_token
{
	char			*value;
	enum e_token	type;
	struct s_token	*next;
}					t_token;
*/

int		ft_create_tree(t_ctrl *ctrl);
int		ft_swap_node_right(t_ast **n_to_swap);
int		ft_swap_node_left(t_ast **n_to_swap);
int		ft_insert_left(t_ast **n_node, t_ast **n_to_ins);
int		ft_insert_right(t_ast **n_node, t_ast **n_to_ins);


int		ft_create_tree(t_ctrl *ctrl) // A GENERER SELON TOKENS PAS FINI PAS FINI PAS FINI PAS FINI
{
	t_ast *tmp;

	if (!ctrl->tk_start)
		return (-1);
	if (!ctrl->ast_start)
	{
		tmp = (*ctrl)->tk_start;
		(*ctrl)->start = tk_tmp;
	}
	// parcourir le tableau, start reste a nul au depart, aller ds le node de gauche, puis remonter pr mettre le premier op, puis droite, etc
	tmp = tmp->next;
	return (0);
}

int		ft_swap_node_right(t_ast **n_to_swap)
{
	t_ast	*tmp;

	tmp = *n_to_swap;
	if (!(*n_to_swap)->right)
		return (-1);
	*n_to_swap = *(n_to_swap)->right;
	*(n_to_swap)->right = tmp;
	return (0);
}

int		ft_swap_node_left(t_ast **n_to_swap)
{
	t_ast	*tmp;

	tmp = *n_to_swap;
	if (!(*n_to_swap)->right)
		return (-1);
	*n_to_swap = *(n_to_swap)->left;
	*(n_to_swap)->left = tmp;
	return (0);
}

int		ft_insert_left(t_ast **n_node, t_ast **n_to_ins)
{
	if (!(n_node) || !(*n_to_ins))
		return (-1);
	(*n_node)->left = *n_to_ins;
	return (0);
}

int		ft_insert_right(t_ast **n_node, t_ast **n_to_ins)
{
	if (!(n_node) || !(*n_to_ins))
		return (-1);
	(*n_node)->right = *n_to_ins;
	return (0);
}
