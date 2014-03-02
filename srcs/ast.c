/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:50:14 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/02 19:57:03 by mgarcin          ###   ########.fr       */
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

int		ft_fill_tree(t_ctrl *ctrl);
int		ft_swap_node_right(t_ast **n_to_swap);
int		ft_swap_node_left(t_ast **n_to_swap);
int		ft_insert_left(t_ast **n_node, t_ast **n_to_ins);
int		ft_insert_right(t_ast **n_node, t_ast **n_to_ins);


int		ft_create_tree(t_ctrl **ctrl)
{
	t_token	*token;

	token = tk_start;
	if (token)
		return (-1);
	while (token)
	{
		ft_fill_tree(ctrl, token);
		token = token->next;
	}
}

int		ft_fill_tree(t_ctrl **ctrl, t_token *token) // A GENERER SELON TOKENS PAS FINI PAS FINI PAS FINI PAS FINI
{
	t_ast 	*tmp;

	tmp = ctrl->ast_start;
	if (token->type == OPERATOR)
	{
		if (tmp && tmp->type == OPERATOR)
		{
			while (tmp->right->tk)
				tmp = tmp->right;
			tmp->right->tk = token;
		}
		else if (tmp && tmp->type == STRING)
		{
			ft_swap_node_left(ctrl->ast_start);
			ctrl->ast_start->tk = token;
		}
		else
			ctrl->ast_start->tk = token;
	} // DONE
	else if (token->type == STRING)
	{
		if (tmp->tk->type == STRING && !tmp->tk->left) // gauche puis centre puis droite
		{
			ctrl->ast_start->tk = token;
			ft_swap_node_left(ctrl->ast_start);
		}
		if (tmp->tk->type == OPERATEUR)
		{
			if (tmp->tk->left->type) // damnit

		}
	{
	else
	{
		ft_putendl("Error token type\n")
		return (-1)
	}
	// parcourir le tableau, start reste a nul au depart, aller ds le node de gauche, puis remonter pr mettre le premier op, puis droite, etc
	tmp = tmp->next;
	}
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
