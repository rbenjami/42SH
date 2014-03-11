/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 14:23:16 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/11 12:24:47 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		(*find_builtin(char *cmd))(char **)
{
	int					i;
	static t_find		tbl[7] =
	{
		{"cd", &builtin_cd},
		{"echo", &builtin_echo},
		{"exit", &builtin_exit},
		{"env", &builtin_env},
		{"setenv", &builtin_setenv},
		{"unsetenv", &builtin_unsetenv},
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
