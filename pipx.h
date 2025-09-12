/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:37:20 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/12 22:32:25 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPX_H
# define PIPX_H

# include "libftprintf/ft_printf.h"
# include "libftprintf/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

char	*cmnd_path(char **envp, char **cmd, int *exit_id);
void	free_list(char **list);

#endif