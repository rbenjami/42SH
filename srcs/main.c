/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 16:00:07 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/24 18:53:52 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <termcap.h>
#include "sh.h"

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

void	prompt(int i, char *logname, char *pwd, char *home)
{
	ft_putstr("\033[40m");
	if ((logname = ft_getenv("LOGNAME")))
		ft_putstr(logname);
	ft_putstr("\033[m\033[44m\033[30m");
	if ((pwd = ft_getenv("PWD")) && (home = ft_getenv("HOME"))
		&& !ft_strncmp(pwd, home, ft_strlen(home)))
	{
		ft_putstr("~");
		i = ft_strlen(home);
	}
	if (pwd)
		ft_putstr(pwd + i);
	if (handler.cmd == 0)
		ft_putstr("\033[m\033[32m");
	else
	{
		ft_putstr("\033[m\033[31m ");
		ft_putnbr(handler.cmd);
	}
	ft_putstr(" ~> \033[m");
	ft_strdel(&home);
	ft_strdel(&logname);
	ft_strdel(&pwd);
}

void	init_env(char **env)
{
	char	**add;
	char	*lvl;

	if (ft_tablen(env) == 0)
		handler.env = default_env();
	else
	{
		handler.env = ft_cpytab(env, ft_tablen(env));
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
	handler.cmd = 0;
}

void	turn_on(struct termios *term)
{
	char	buffer[2048];

	if (tgetent(buffer, getenv("TERM")) < 1)
	{
		write(2, "TERM: not found\n", 16);
		exit(0);
	}
	tcgetattr(0, term);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	tcsetattr(0, 0, term);
}

int		main(void)
{
	char		*line;
	t_token		*token;
	t_ast		*tree;
	extern char	**environ;
	struct termios		term;

	turn_on(&term);
	init_env(environ);
	init_op(&handler.tab_op);
	while (1)
	{
		tree = NULL;
		token = NULL;
		prompt(0, "", "", "");
		if (!(line = reader(0)))
			exit(-1);
		handler.cmd = 0;
		lexer(&token, line);
		parse_string(&token);
		ft_strdel(&line);
		ft_modify_token_for_redir(&token);
		if (token)
			fill_tree(token, &tree);
		resolve_tree(tree, NULL);
		free_ast(&tree);
	}
	return (0);
}
