/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 14:23:16 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/26 16:27:07 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int (*find_builtin(char *cmd))(char **)
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
	while (tbl[i].f && ft_strcmp(tbl[i].cmd, cmd))
		i++;
	if (tbl[i].f)
		return (tbl[i].f);
	else
		return (NULL);
}
