/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 13:44:39 by smakroum          #+#    #+#             */
/*   Updated: 2014/03/04 15:34:36 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// typedef struct		s_token
// {
// 	char			*value;
// 	int				type;
// 	struct s_token	*next;
// }					t_token;

// typedef struct		s_ast
// {
// 	t_token			*tk;
// 	struct s_ast	*left;
// 	struct s_ast	*right;
//	struct s_ast	*father;
// }					t_ast;

void	ft_add_node(t_ast **tree, t_token *tk)
{
	*tree = (t_ast *)malloc(sizeof(t_ast));
	if (*tree)
	{
		(*tree)->tk = tk;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
}

///////////////////	DEBUG !

void		ft_putlst(t_token *tk)
{
	while (tk && tk->next)
	{
		ft_putstr(tk->value);
		ft_putstr(" -> ");
		tk = tk->next;
	}
	if (tk)
		ft_putendl(tk->value);
}
///////////////////	END DEBUG !

t_token		*ft_lstsub(t_token *start_tk, t_token *tmp_t)
{
	t_token	*new_lst;

	new_lst = start_tk;
	while (start_tk && start_tk->next != tmp_t)
		start_tk = start_tk->next;
	if (start_tk)
		start_tk->next = NULL;
	return (new_lst);
}

void		fill_tree(t_token *tk, t_ast **tree)
{
	t_token *tmp_t;
	t_token *start_tk;
	t_token *left;
	t_token *right;

	tmp_t = tk;
	start_tk = tk;
	while (tk)
	{
		if (tk->prio > tmp_t->prio)
			tmp_t = tk;
		tk = tk->next;
	}
	if (tmp_t)
		ft_add_node(tree, tmp_t);
	right = (tmp_t) ? tmp_t->next : tmp_t;
	left = ft_lstsub(start_tk, tmp_t);
	if (start_tk != tmp_t)
		fill_tree(left, &(*tree)->left);
	if (right)
	 	fill_tree(right, &(*tree)->right);
}
