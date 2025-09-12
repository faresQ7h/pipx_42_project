/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:02 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/13 00:15:54 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

int	prepar_fds(pid_t pid, int *fd, int **pip, char **argv)
{
	if (pid != 0)
	{
		*fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*fd < 0)
			return (close((*pip)[0]), close((*pip)[1]), -1);
		close((*pip)[1]);
		if (dup2((*pip)[0], STDIN_FILENO) == -1 || dup2(*fd, STDOUT_FILENO) ==
			-1)
			return (close(*fd), close((*pip)[0]), -1);
	}
	else
	{
		*fd = open(argv[1], O_RDONLY);
		if (*fd < 0)
			return (close((*pip)[0]), close((*pip)[1]), -1);
		close((*pip)[0]);
		if (dup2(*fd, STDIN_FILENO) == -1 || dup2((*pip)[1], STDOUT_FILENO) ==
			-1)
			return (close(fd), close((*pip)[1]), -1);
	}
	return (0);
}

void	print_id(int exit_id, char *cmd_nm)
{
	if (exit_id == 126)
		return (ft_putstr_fd(cmd_nm, 2), ft_putstr_fd(": Permission denied",
				2));
	else if (exit_id == 127)
		return (ft_putstr_fd("command not found: ", 2), ft_putstr_fd(cmd_nm,
				2));
	else
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	int		i;
	int		exit_id;
	int		pip[2];
	pid_t	pid;
	char	*path;
	char	**cmd;

	if (argc != 5)
		return (ft_putstr_fd("Error\nUsage: ./pipex file1 cmd1 cmd2 file2\n",2), 1);
	if (pipe(*pip) < 0)
		return (-1);
	pid = fork();
    if (pid < 0)
        return(perror("fork"), errno);
	if (pid != 0)
	{
		if (prepar_fds(pid, &fd, &pip, argv) == -1)
			return (perror("Error cmd2"), errno);
		i = 1;
	}
	else
	{
		if (prepar_fd(pid, &fd, &pip, argv))
			return (perror("Error cmd1"), 1);
		i = 0;
	}
	exit_id = 0;
	cmd = ft_split(argv[2 + i], ' ');
	path = cmnd_path(envp, cmd, &exit_id);
	if (!path)
		return (print_id(exit_id, cmd[0]), close(pip[1 - i]), close(fd),
			free_list(cmd), exit_id);
	return (close(pip[1 - i]), close(fd), free_list(cmd), 0);
}
