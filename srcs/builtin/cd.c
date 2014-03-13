/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:45:13 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/13 14:07:30 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh.h"

void			ft_setenv(char *name, char *value)
{
	char *av[5];

	av[0] = "setenv";
	av[1] = name;
	av[2] = value;
	av[3] = "1";
	av[4] = NULL;
	builtin_setenv(av);
}

static int		ft_isdir(char *file)
{
	struct stat	*file_mode;

	file_mode = ft_memalloc(sizeof(struct stat));
	lstat(file, file_mode);
	if (S_ISDIR(file_mode->st_mode))
	{
		free(file_mode);
		return (1);
	}
	free(file_mode);
	return (0);
}

static void		ft_cd_permission_denied(char *path)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Permission denied", 2);
}

static void		ft_cd2(char *path, int cmp)
{
	char	buf[256];

	if (!path)
	{
		if (!(path = ft_getenv("HOME")))
		{
			ft_putendl_fd("bash: cd: HOME not set", 2);
			return ;
		}
	}
	else if (cmp == 0)
	{
		path = ft_getenv("OLDPWD");
		if (!path)
			ft_putendl_fd("bash: cd: OLDPWD not set", 2);
	}
	if (path && access(path, X_OK) == -1)
		ft_cd_permission_denied(path);
	else
	{
		if (path)
			ft_setenv("OLDPWD", getcwd(buf, 256) + 13);
		chdir(path);
		ft_setenv("PWD", getcwd(buf, 256) + 13);
	}
}

int			builtin_cd(char **argv)
{
	int		cmp;
	char	*path;

	cmp = -1;
	path = argv[1];
	if (ft_isdir(path) || !path || (cmp = ft_strcmp(path, "-")) == 0)
	{
		ft_cd2(path, cmp);
		return (0);
	}
	return (error(path, ": No such file or directory"));
}
