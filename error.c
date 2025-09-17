/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:29:16 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/18 01:45:43 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

int	parse_exit_id(int st)
{
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	if (WIFSIGNALED(st))
		return (128 + WTERMSIG(st));
	return (1);
}

int	exit_code(int e)
{
	if (e == ENOENT)
		return (127);
	else if (e == EACCES || e == EPERM || e == EISDIR || e == ENOEXEC)
		return (126);
	else
		return (1);
}

void	print_id(int exit_id, char *cmd_nm, int execve)
{
	if (!execve)
	{
		if (exit_id == 126)
			return (ft_putstr_fd(cmd_nm, 2),
				ft_putstr_fd(": Permission denied\n", 2));
		else if (exit_id == 127 && ft_strchr(cmd_nm, '/') != NULL)
			return (ft_putstr_fd(cmd_nm, 2),
				ft_putstr_fd(": No such file or directory\n", 2));
		else if (exit_id == 127)
			return (ft_putstr_fd("command not found: ", 2), ft_putstr_fd(cmd_nm,
					2), ft_putstr_fd("\n", 2));
	}
	if (ft_strchr(cmd_nm, '/') == NULL && exit_id == ENOENT)
		return (ft_putstr_fd("command not found: ", 2), ft_putstr_fd(cmd_nm, 2),
			ft_putstr_fd("\n", 2));
	else
		perror(cmd_nm);
}

char	**fall_back(char **path, char **cmd)
{
	int		len;
	int		i;
	char	**new_cmd;

	free(*path);
	*path = ft_strdup("/bin/sh");
	if (!*path)
		return (NULL);
	len = 0;
	while (cmd[len])
		len++;
	new_cmd = malloc(sizeof(char *) * (len + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	len = 0;
	new_cmd[i] = ft_strdup("/bin/sh");
	if (!new_cmd[i])
		return (free(new_cmd), NULL);
	i++;
	while (cmd[len])
		new_cmd[i++] = cmd[len++];
	new_cmd[i] = NULL;
	return (free(cmd), new_cmd);
}
