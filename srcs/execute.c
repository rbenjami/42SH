/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 15:56:25 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/14 18:44:46 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh.h"

int			find_arg_path()
{
	int				i;

	i = 0;
	while (handler.env[i])
	{
		if (!(ft_strncmp(handler.env[i], "PATH", 4)))
			return (i);
		i++;
	}
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

	if (ft_strchr(cmd, '/'))
		return (cmd);
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

int			ft_isfuncfork(char *name)
{
	if (ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "setenv") == 0
		|| ft_strcmp(name, "unsetenv") == 0
		|| ft_strcmp(name, "exit") == 0)
		return (0);
	return (1);
}

pid_t		execute(char *cmd, int	pfd_old[2], int	pfd[2], int b)
{
	char			**args;
	char			*path;
	pid_t			pid;
	int				ret;
	int				(*builtin)(char **);

	if (!cmd[0])
		return (error("permission denied: ", NULL));
	if ((args = ft_strsplit_space(cmd)) == NULL)
		return (error("command not found: ", NULL));
	builtin = find_builtin(args[0]);
	path = find_path(args[0], handler.env, find_arg_path());
	if (!path && !builtin)
	{
		ft_free_tab(&args);
		return (error("command not found: ", cmd));
	}
	if (builtin && (ret = ft_isfuncfork(args[0])) == 0)
	{
		if (builtin(args) < 0)
			return (-1);
	}
	if ((pid = fork()) < 0)
		return (error("fork error !", NULL));
	if (pid == 0)
	{
		if (pfd || pfd_old)
			dup_close(pfd, pfd_old, b);
		if (builtin)
		{
			if  (ret && builtin(args) < 0)
				exit(1);
			exit(0);
		}
		else if (execve(path, args, handler.env) == -1)
			exit(1);
	}
	ft_free_tab(&args);
	if (path[0])
		free(path);
	return (pid);
}
