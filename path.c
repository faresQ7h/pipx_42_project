/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:09:44 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/12 23:18:14 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

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

char	*search_paths(char **__paths, char **cmd, int *exit_id)
{
	int		i;
	char	*path;
	char	*cmd_nm;

	cmd_nm = ft_strjoin("/", cmd[0]);
	if (!cmd_nm)
		return (NULL);
	i = 0;
	path = NULL;
	while (__paths[i])
	{
		if (path)
			free(path);
		path = ft_strjoin(__paths[i], cmd_nm);
		if (!path)
			return (free(cmd_nm), NULL);
		check_access(&path, cmd_nm, exit_id);
		i++;
	}
	*exit_id = 127;
	return (free(cmd_nm), free(path), NULL);
}

int	check_access(char **path, char *cmd, int *exit_id)
{
	*path = NULL;
	if (!access(cmd, F_OK | X_OK))
	{
		*path = cmd;
		return (0);
	}
	else if (!access(cmd[0], F_OK) && access(cmd, X_OK))
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

char	*cmnd_path(char **envp, char **cmd, int *exit_id)
{
	int		i;
	char	*path;
	char	**__paths;

	*exit_id = 1;
	if (!cmd)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		__paths = ft_split(envp[i] + 5, ':');
	if (!__paths)
		return (NULL);
	if (ft_strchr(cmd[0], '/') != NULL)
		check_access(&path, cmd[0], exit_id);
	else
		path = search_paths(__paths, cmd, &exit_id);
	if (!path)
		return (free_list(__paths), NULL);
	return (free_list(__paths), path);
}
