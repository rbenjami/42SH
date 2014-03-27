/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 14:23:16 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/27 16:03:46 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_buil		find_builtin(char *cmd)
{
	int					i;
	static t_find		tbl[8] =

	{
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{"history", &builtin_history},
	{NULL, NULL}
	};
	i = 0;
	while (tbl[i].find && ft_strcmp(tbl[i].cmd, cmd))
		i++;
	if (tbl[i].find)
		return (tbl[i].find);
	else
		return (NULL);
}
