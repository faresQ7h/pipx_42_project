/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:37:20 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/18 01:36:05 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPX_H
# define PIPX_H

# include "libftprintf/ft_printf.h"
# include "libftprintf/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

char	*trim_str(char *str, int i, int j, int in_q);
char	**split_cmd(char *cmd);
char	*cmnd_path(char **envp, char **cmd, int *exit_id);
void	*free_return(char **list, int len);
void	free_list(char **list);
int		exit_code(int e);
void	print_id(int exit_id, char *cmd_nm, int execve);
int		parse_exit_id(int exit_id);
char	**fall_back(char **path, char **cmd);

#endif