/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/13 14:23:51 by rbenjami         ###   ########.fr       */
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

void	prompt()
{
	int		i;
	char	*pwd;
	char	*home;

	i = 0;
	pwd = ft_getenv("PWD");
	home = ft_getenv("HOME");
	ft_putstr("\033[40m");
	ft_putstr(ft_getenv("LOGNAME"));
	ft_putstr("\033[m\033[44m\033[30m");
	if (!ft_strncmp(pwd, home, ft_strlen(home)))
	{
		ft_putstr("~");
		i = ft_strlen(home);
	}
	ft_putstr(pwd + i);
	if (handler.cmd == 0)
		ft_putstr("\033[m\033[32m");
	else
	{
		ft_putstr("\033[m\033[31m ");
		ft_putnbr(handler.cmd);
	}
	ft_putstr(" ~> \033[m");
}

int		main(void)
{
	char		*line;
	t_token		*token;
	t_ast		*tree;
	extern char	**environ;

	init_op(&handler.tab_op);
	handler.environ = ft_cpytab(environ, ft_tablen(environ));
	handler.cmd = 0;
	while (1)
	{
		tree = NULL;
		token = NULL;
		prompt();
		handler.cmd = 0;
		if (get_next_line(0, &line) <= 0)
			exit(0);
		lexer(&token, line);
		parse_string(&token);
		free(line);
		if (token)
			fill_tree(token, &tree);
		resolve_tree(tree, NULL);
		free_ast(&tree);
	}
	return (0);
}
