/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/10 13:45:16 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

///////////////////	DEBUG !

char* tab_type[2] =
{
	"STRING",
	"OPERATOR"
};

void	DEBUG(t_token *token)
{
	while (token)
	{
		ft_putstr("\033[32mTYPE: \033[33m");
		ft_putstr(tab_type[token->type]);
		ft_putstr("\033[m : \033[31m");
		ft_putnbr(token->type);
		ft_putstr("\n\033[32mVALUE: \033[33m");
		ft_putendl(token->value);
		ft_putstr("\033[32mPRIORITY: \033[33m");
		ft_putnbr(token->prio);
		ft_putstr("\n\n\033[0m");
		token = token->next;
	}
}

void	DEBUG2(t_ast *tree)
{
	if (tree)
	{
		ft_putstr("\033[32mTYPE: \033[33m");
		ft_putstr(tab_type[tree->tk->type]);
		ft_putstr("\033[m : \033[31m");
		ft_putnbr(tree->tk->type);
		ft_putstr("\n\033[32mVALUE: \033[33m");
		ft_putendl(tree->tk->value);
		ft_putstr("\033[32mPRIORITY: \033[33m");
		ft_putnbr(tree->tk->prio);
		ft_putstr("\n\n\033[0m");
		DEBUG2(tree->left);
		DEBUG2(tree->right);
	}
}
///////////////////	DEBUG !

void	free_token(t_token **token)
{
	t_token		*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_ast(t_ast **tree)
{
	if (*tree)
	{
		free_ast(&(*tree)->left);
		free_ast(&(*tree)->right);
		// ft_putstr("delete : ");
		// ft_putendl((*tree)->tk->value);
		free((*tree)->tk->value);
		(*tree)->tk->value = NULL;
		free((*tree)->tk);
		(*tree)->tk = NULL;
		free(*tree);
		*tree = NULL;
	}
}

int		main(void)
{
	char		*line;
	t_token		*token;
	t_ast		*tree;

	init_op(&tab_op);
	while (1)
	{
		tree = NULL;
		token = NULL;
		ft_putstr("~> ");
		if (get_next_line(0, &line) <= 0)
			exit(0);
		// execute(line);
		lexer(&token, line);
		// DEBUG(token);
		free(line);
		if (token)
			fill_tree(token, &tree);
		resolve_tree(tree, NULL);
		//DEBUG2(tree);
		free_ast(&tree);
	}
	return (0);
}
