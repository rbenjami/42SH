/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:24:53 by mgarcin           #+#    #+#             */
/*   Updated: 2014/03/04 15:34:39 by rbenjami         ###   ########.fr       */
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

t_ast	*ft_malloc_n(t_ast *father, t_token *tk)
{
	t_ast	*new_tree;

	new_tree = (t_ast *)malloc(sizeof(t_ast));
	if (!new_tree)
		return (NULL);
	new_tree->father = father;
	new_tree->tk = tk;
	new_tree->left = NULL;
	new_tree->right = NULL;
	return (new_tree);
}

void	ft_add_node(t_token *start, t_token *tk, t_ast **tree)
{
	(*tree)->tk = tk;
	if ((*tree)->tk != start)
		(*tree)->left = ft_malloc_n(*tree, start);
	if ((*tree)->tk->next != NULL)
		(*tree)->right = ft_malloc_n(*tree, tk->next);
}

int		init_tree(t_token *tk, t_ast **tree)
{
	if (!tk)
		return (-1);
	if (!(*tree))
		(*tree) = ft_malloc_n(NULL, NULL);
	fill_tree(tk, tree);
	return (0);
}

int		fill_tree(t_token *tk, t_ast **tree)
{
	t_token *tmp_t;
	t_token *start_tk;

	start_tk = tk;
	tmp_t = tk;
	while (tk && (*tree)->father && (*tree)->father->tk != tk) // ICI < --------------------------------------------------------
	{
		if (tk->prio > tmp_t->prio)
			tmp_t = tk;
		tk = tk->next;
	}
	ft_add_node(start_tk, tmp_t, tree);
	if (start_tk != tmp_t)
		return (fill_tree(start_tk, &(*tree)->left));
	if (tmp_t->next)
		return (fill_tree(tmp_t->next, &(*tree)->right));
	return (0);
}
