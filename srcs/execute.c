/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 15:56:25 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/11 12:45:48 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh.h"

int			find_arg_path(char **environ)
{
	int				i;

	i = 0;
	while (environ[i])
	{
		if (!(ft_strncmp(environ[i], "PATH", 4)))
			return (i);
		i++;
	}
	error("no path in env: ", NULL);
	return (-1);
}

int			is_dir(char *cmd, char *path)
{
	DIR				*rep;
	struct dirent	*lecture;

	rep = opendir(path);
	if (rep == NULL)
		return (-1);
	lecture = readdir(rep);
	while (lecture)
	{
		if (ft_strcmp(cmd, lecture->d_name) == 0)
		{
			closedir(rep);
			return (1);
		}
		lecture = readdir(rep);
	}
	closedir(rep);
	return (0);
}

char		*find_path(char *cmd, char **environ, int i)
{
	static char	**path = NULL;
	char		*res;
	char		*tmp;
	int			j;

	if (i == -1)
		return (NULL);
	j = 0;
	if (!path)
		path = ft_strsplit(&environ[i][5], ':');
	while (path[j])
	{
		if (is_dir(cmd, path[j]) == 1)
		{
			tmp = ft_strjoin(path[j], "/");
			res = ft_strjoin(tmp, cmd);
			free(tmp);
			return (res);
		}
		j++;
	}
	return (NULL);
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

pid_t		execute(char *cmd, int	pfd_old[2], int	pfd[2], int b)
{
	char			**args;
	char			*path;
	pid_t			pid;
	int				(*builtin)(char **);

	if (!cmd[0])
		return (error("permission denied: ", NULL));
	if ((args = ft_strsplit_space(cmd)) == NULL)
		return (error("command not found: ", NULL));
	builtin = find_builtin(args[0]);
	path = find_path(args[0], environ, find_arg_path(environ));
	if (!path && !builtin)
		error("command not found: ", cmd);
	if ((pid = fork()) < 0)
		error("fork error !", NULL);
	if (pid == 0)
	{
		if (pfd || pfd_old)
			dup_close(pfd, pfd_old, b);
		if (builtin && builtin(args) == -1)
			exit(1);
		else if (!builtin && execve(path, args, environ) == -1)
			exit(1);
	}
	ft_free_tab(&args);
	if (path)
		free(path);
	return (pid);
}
