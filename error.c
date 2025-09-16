/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:29:16 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/15 23:02:55 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

int	parse_exit_id(int exit_id)
{
	if (WIFEXITED(exit_id))
	{
		if (WEXITSTATUS(exit_id) == 127)
			return (127);
		else if (WEXITSTATUS(exit_id) == 126)
			return (126);
		else if (WEXITSTATUS(exit_id) == 1)
			return (1);
	}
	else if (WIFSIGNALED(exit_id))
		return (128 + WTERMSIG(exit_id));
	return (0);
}

void	print_id(int exit_id, char *cmd_nm)
{
	if (exit_id == 126)
		return (ft_putstr_fd(cmd_nm, 2), ft_putstr_fd(": Permission denied\n",
				2));
	else if (exit_id == 127 && ft_strchr(cmd_nm, '/') != NULL)
		return (ft_putstr_fd(cmd_nm, 2),
			ft_putstr_fd(": No such file or directory\n", 2));
	else if (exit_id == 127)
		return (ft_putstr_fd("Command not found: ", 2), ft_putstr_fd(cmd_nm, 2),
			ft_putstr_fd("\n", 2));
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
