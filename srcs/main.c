/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 14:44:28 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

void	init_env(char **env)
{
	char	**add;
	char	*lvl;

	handler.env = ft_cpytab(env, ft_tablen(env));
	handler.cmd = 0;
	lvl = ft_getenv("SHLVL");
	add = ft_memalloc(sizeof(char *) * 4);
	add[1] = ft_strdup("SHLVL");
	add[2] = ft_itoa(ft_atoi(lvl) + 1);
	add[3] = ft_strdup("1");
	builtin_setenv(add);
	ft_strdel(&add[1]);
	ft_strdel(&add[2]);
	ft_strdel(&add[3]);
	ft_free_tab(&add);
}

int		main(void)
{
	char		*line;
	t_token		*token;
	t_ast		*tree;
	extern char	**environ;

	init_env(environ);
	init_op(&handler.tab_op);
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
