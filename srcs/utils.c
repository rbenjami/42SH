/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 12:25:29 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 23:10:28 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		close_pfd(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

void		dup_close(int *pfd, int *pfd_old, int b)
{
	if (pfd_old && b)
	{
		close(pfd_old[b]);
		close(!b);
		dup2(pfd_old[!b], !b);
	}
	close(pfd[!b]);
	close(b);
	dup2(pfd[b], b);
}

int			ft_isfuncfork(char *name)
{
	if (ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "setenv") == 0
		|| ft_strcmp(name, "unsetenv") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (0);
	return (1);
}

char		**default_env(void)
{
	char	**environ;
	char	buf[256];
	char	*pwd;

	pwd = ft_strdup(getcwd(buf, 256) + 13);
	environ = (char **)ft_memalloc(sizeof(char *) * 7);
	environ[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:\
		/opt/X11/bin:/usr/texbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
		/opt/X11/bin:/usr/texbin");
	environ[1] = ft_strdup("SHLVL=1");
	environ[2] = ft_strdup("PWD=");
	ft_strjoin2(&environ[2], pwd);
	ft_strdel(&pwd);
	environ[3] = ft_strdup("OLDPWD=/");
	environ[4] = ft_strdup("HOME=/");
	environ[5] = ft_strdup("LOGNAME=roger");
	environ[6] = NULL;
	ft_putendl("pok");
	return (environ);
}
