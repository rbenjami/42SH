/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 14:23:16 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/26 19:32:07 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_find		*init_tab(void)
{
	t_find	*tbl;

	if (!(tbl = (t_find *)ft_memalloc(sizeof(t_find) * 8)))
		return (NULL);
	tbl[0].cmd = "cd";
	tbl[0].find = &builtin_cd;
	tbl[1].cmd = "echo";
	tbl[1].find = &builtin_echo;
	tbl[2].cmd = "exit";
	tbl[2].find = &builtin_exit;
	tbl[3].cmd = "env";
	tbl[3].find = &builtin_env;
	tbl[4].cmd = "setenv";
	tbl[4].find = &builtin_setenv;
	tbl[5].cmd = "unsetenv";
	tbl[5].find = &builtin_unsetenv;
	tbl[6].cmd = "history";
	tbl[6].find = &builtin_history;
	return (tbl);
}

int (*find_builtin(char *cmd))(char **)
{
	int					i;
	static t_find		*tbl = NULL;

	if (!tbl)
		tbl = init_tab();
	i = 0;
	while (tbl[i].find && ft_strcmp(tbl[i].cmd, cmd))
		i++;
	if (tbl[i].find)
		return (tbl[i].find);
	else
		return (NULL);
}
