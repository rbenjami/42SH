/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 18:45:13 by dsousa            #+#    #+#             */
/*   Updated: 2014/03/26 16:02:25 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh.h"

void			ft_setenv(char *name, char *value)
{
	char	**av;

	av = (char **)ft_memalloc(sizeof(char *) * 5);
	av[0] = ft_strdup("setenv");
	av[1] = ft_strdup(name);
	av[2] = ft_strdup(value);
	av[3] = ft_strdup("1");
	av[4] = NULL;
	builtin_setenv(av);
	ft_free_tab(&av);
}

static int		ft_isdir(char *file)
{
	struct stat		*file_mode;

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

static void		ft_cd2(char *path, int cmp)
{
	char	buf[256];

	if (!path && !(path = ft_getenv("HOME")))
		error("42sh: cd: HOME not set\n");
	else if (cmp == 0)
	{
		ft_strdel(&path);
		if (!(path = ft_getenv("OLDPWD")))
			error("42sh: cd: OLDPWD not set\n");
	}
	if (path && access(path, X_OK) == -1)
		error("42sh: %s: Permission denied\n", path);
	else if (path)
	{
		ft_setenv("OLDPWD", getcwd(buf, 256) + 13);
		chdir(path);
		ft_setenv("PWD", getcwd(buf, 256) + 13);
	}
	ft_strdel(&path);
}

int				builtin_cd(char **argv)
{
	int		cmp;
	char	*path;

	cmp = -1;
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		path = NULL;
	else
		path = ft_strdup(argv[1]);
	if (ft_isdir(path) || !path || (cmp = ft_strcmp(path, "-")) == 0)
	{
		ft_cd2(path, cmp);
		return (0);
	}
	return (error("%s: No such file or directory\n", path));
}
