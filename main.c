/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:02 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/14 03:24:46 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

void	print_id(int exit_id, char *cmd_nm)
{
	if (exit_id == 126)
		return (ft_putstr_fd(cmd_nm, 2), ft_putstr_fd(": Permission denied\n",
				2));
	else if (exit_id == 127)
		return (ft_putstr_fd("command not found: ", 2), ft_putstr_fd(cmd_nm, 2),
			ft_putstr_fd("\n", 2));
	else
		return ;
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

int	init_role_and_pipe(int pip[2], int argc)
{
	int	is_parent;

	if (argc != 5)
		return (ft_putstr_fd("Error\nUsage: ./pipex file1 cmd1 cmd2 file2\n",
				2), -1);
	if (pipe(pip) < 0)
		return (perror("pipe"), -1);
	is_parent = fork();
	if (is_parent < 0)
		return (close(pip[0]), close(pip[1]), perror("fork"), -1);
	return (is_parent != 0);
}

int	prepar_fds(int is_parent, int pip[2], char **argv)
{
	int	fd;

	if (is_parent == 1)
	{
		fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (close(pip[0]), close(pip[1]), perror("Error cmd2"), -1);
		close(pip[1]);
		if (dup2(pip[0], STDIN_FILENO) == -1 || dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), close(pip[0]), perror("Error cmd2"), -1);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (close(pip[0]), close(pip[1]), perror("Error cmd1"), -1);
		close(pip[0]);
		if (dup2(fd, STDIN_FILENO) == -1 || dup2(pip[1], STDOUT_FILENO) == -1)
			return (close(fd), close(pip[1]), perror("Error cmd1"), -1);
	}
	return (close(fd), 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		is_parent;
	int		exit_id;
	int		pip[2];
	char	*path;
	char	**cmd;

	is_parent = init_role_and_pipe(pip, argc);
	if (is_parent == -1 || prepar_fds(is_parent, pip, argv) == -1)
		return (1);
	exit_id = 0;
	cmd = ft_split(argv[2 + is_parent], ' ');
	if (!cmd)
		return (perror("malloc"), close(pip[1 - is_parent]), 1);
	if (!cmd[0] || !*cmd[0])
		return (ft_putstr_fd("command not found: \n", 2), free_list(cmd), 127);
	path = cmnd_path(envp, cmd, &exit_id);
	if (!path)
		return (print_id(exit_id, cmd[0]), free_list(cmd), close(pip[1
					- is_parent]), exit_id);
	exit_id = errno;
	execve(path, cmd, envp);
	return (perror(cmd[0]), free(path), free_list(cmd), close(pip[1
				- is_parent]), exit_code(exit_id));
}
