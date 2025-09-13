/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:09:44 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/13 23:09:27 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

char	*set_return(int *exit_id, int set)
{
	*exit_id = set;
	return (NULL);
}

void	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

int	check_access(char *cmd_path, int *exit_id)
{
	if (!access(cmd_path, X_OK))
		return (0);
	else if (!access(cmd_path, F_OK))
	{
		*exit_id = 126;
		return (-1);
	}
	else
	{
		*exit_id = 127;
		return (-1);
	}
}

char	*search_paths(char **__paths, char **cmd, int *exit_id)
{
	int		i;
	char	*path;
	char	*cmd_nm;

	cmd_nm = ft_strjoin("/", cmd[0]);
	if (!cmd_nm)
		return (perror("malloc"), set_return(exit_id, 1));
	i = 0;
	path = NULL;
	while (__paths[i])
	{
		if (path)
			free(path);
		path = ft_strjoin(__paths[i], cmd_nm);
		if (!path)
			return (free(cmd_nm), perror("malloc"), set_return(exit_id, 1));
		if (check_access(path, exit_id) == 0)
			return (free(cmd_nm), path);
		i++;
	}
	*exit_id = 127;
	return (free(cmd_nm), free(path), NULL);
}

char	*cmnd_path(char **envp, char **cmd, int *exit_id, int is_parent)
{
	int		i;
	char	*path;
	char	**__paths;

	if (ft_strchr(cmd[0], '/') != NULL && !check_access(cmd[0], exit_id))
	{
		path = ft_strdup(cmd[0]);
		if (!path)
			return (perror("malloc"), set_return(exit_id, 1));
		return (path);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		__paths = ft_split(envp[i] + 5, ':');
	else
		return (set_return(exit_id, 127));
	if (!__paths)
		return (perror("malloc"), set_return(exit_id, 1));
	path = search_paths(__paths, cmd, exit_id);
	free_list(__paths);
	if (!path)
		return (set_return(exit_id, 1));
	return (path);
}
