/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/27 18:36:46 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_ast(t_ast **tree)
{
	t_redir	*tmp;

	if (*tree)
	{
		free_ast(&(*tree)->left);
		free_ast(&(*tree)->right);
		free((*tree)->tk->value);
		(*tree)->tk->value = NULL;
		while ((*tree)->tk->redir)
		{
			tmp = (*tree)->tk->redir;
			(*tree)->tk->redir = (*tree)->tk->redir->next;
			free(tmp->name);
			free(tmp);
		}
		free((*tree)->tk);
		(*tree)->tk = NULL;
		free(*tree);
		*tree = NULL;
	}
}

void	init_env(char **env)
{
	char	**add;
	char	*lvl;

	if (ft_tablen(env) == 0)
		g_handler.env = default_env();
	else
	{
		g_handler.env = ft_cpytab(env, ft_tablen(env));
		lvl = ft_getenv("SHLVL");
		add = ft_memalloc(sizeof(char *) * 4);
		add[1] = ft_strdup("SHLVL");
		add[2] = (lvl) ? ft_itoa(ft_atoi(lvl) + 1) : ft_strdup("1");
		add[3] = ft_strdup("1");
		builtin_setenv(add);
		ft_strdel(&lvl);
		ft_strdel(&add[1]);
		ft_strdel(&add[2]);
		ft_strdel(&add[3]);
		ft_free_tab(&add);
	}
	g_handler.cmd = 0;
	g_handler.len = 0;
}

void	sig_g_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	prompt();
}

void	loop(t_token *token, t_ast *tree)
{
	char				*line;
	int					b;

	tree = NULL;
	token = NULL;
	signal(SIGINT, &sig_g_handler);
	prompt();
	if (!(line = reader(0, g_handler.hist)))
		exit(-1);
	if (line && line[0] != '\n')
		save_hist(g_handler.hist->start, line, 1, g_handler.hist);
	g_handler.cmd = 0;
	lexer(&token, line);
	ft_strdel(&line);
	b = parse_string(&token);
	if (token && b != -42 && ft_modify_token_for_redir(&token) != -42)
	{
		fill_tree(token, &tree);
		resolve_tree(tree, NULL);
		free_ast(&tree);
	}
	if (b == -42)
		g_handler.cmd = -42;
	free(line);
}

int		main(void)
{
	extern char			**environ;
	struct termios		term;
	t_token				*token;
	t_ast				*tree;

	tree = NULL;
	token = NULL;
	turn_on(&term);
	init_env(environ);
	g_handler.term = &term;
	init_op(&g_handler.tab_op);
	g_handler.hist = ft_memalloc(sizeof(t_ctrl_h));
	create_hist(g_handler.hist);
	while (1)
		loop(token, tree);
	return (0);
}
