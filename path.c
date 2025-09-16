/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:09:44 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/16 01:31:04 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

char	*set_return(int *exit_id, int set)
{
	*exit_id = set;
	return (NULL);
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

char	*path_has_slash(char *cmd, int *exit_id)
{
	char	*path;

	if (!check_access(cmd, exit_id))
	{
		path = ft_strdup(cmd);
		if (!path)
		{
			perror("malloc");
			*exit_id = 1;
			return (NULL);
		}
		return (path);
	}
	return (NULL);
}

char	*cmnd_path(char **envp, char **cmd, int *exit_id)
{
	int		i;
	char	*path;
	char	**__paths;

	if (ft_strchr(cmd[0], '/') != NULL)
		return (path_has_slash(cmd[0], exit_id));
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
		return (NULL);
	return (path);
}
