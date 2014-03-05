/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakroum <smakroum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 15:56:25 by rbenjami          #+#    #+#             */
/*   Updated: 2014/03/05 19:45:57 by smakroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <libft.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
#include "sh.h"

int		find_arg_path(void)
{
	int				i;
	extern char		**environ;

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

char	*find_path2(char *cmd, char **path)
{
	int				i;
	char			*res;
	char			*tmp;
	DIR				*rep;
	struct dirent	*lecture;

	i = 0;
	while (path[i])
	{
		rep = opendir(path[i]);
		if (rep == NULL)
			return (NULL);
		lecture = readdir(rep);
		while (lecture)
		{
			if (ft_strcmp(cmd, lecture->d_name) == 0)
			{
				res = ft_strjoin(path[i], "/");
				closedir(rep);
				// FUITE MEM !!!!
				tmp = ft_strjoin(res, lecture->d_name);
				free(res);
				return (tmp);
			}
			lecture = readdir(rep);
		}
		closedir(rep);
		i++;
	}
	ft_free_tab(&path);
	return (0);
}

char	*find_path(char *cmd, char **environ)
{
	struct stat		s;
	char			**path;
	int				i;

	stat(cmd, &s);
	if ((s.st_mode & S_IFREG) && cmd[0] == '/')
		return (cmd);
	i = find_arg_path();
	if (i == -1)
		return (NULL);
	path = ft_strsplit(&environ[i][5], ':');
	return (find_path2(cmd, path));
}

pid_t		execute(char *cmd, int	pfd_old[2], int	pfd[2], int b)
{
	char			**args;
	char			*path;
	extern char		**environ;
	pid_t			pid;

	args = ft_strsplit(cmd, ' ');
	path = find_path(args[0], environ);
	if (!path)
		error("command not found: ", cmd);
	if ((pid = fork()) < 0)
		error("fork error !", NULL);
	if (pid == 0)
	{
		if (pfd || pfd_old)
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
		if (execve(path, args, environ) == -1)
			exit(1);
	}
	ft_free_tab(&args);
	free(path);
	return (pid);
}
































