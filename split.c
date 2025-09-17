/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:06:45 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/17 02:23:03 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

void	*free_return(char **list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

int	valid_syntax(const char *cmd)
{
	while (*cmd)
	{
		if (*cmd == 39 || *cmd == 34)
		{
			cmd = ft_strchr(cmd + 1, *cmd);
			if (!cmd)
				return (0);
		}
		cmd++;
	}
	return (1);
}

int	set_start_end(int *start, int *end, const char *cmd, int in_q)
{
	int	open_q;

	*start = *end;
	while (cmd[*start] && cmd[*start] == ' ')
		(*start)++;
	if (!cmd[*start])
		return (0);
	if (cmd[*start] == '"' || cmd[*start] == 39)
	{
		open_q = *start;
		in_q = 1;
	}
	*end = (*start) + 1;
	while (cmd[*end] && (cmd[*end] != ' ' || in_q))
	{
		if (!in_q && (cmd[*end] == '"' || cmd[*end] == 39))
		{
			in_q = 1;
			open_q = *end;
		}
		else if (in_q && cmd[*end] == cmd[open_q])
			in_q = 0;
		(*end)++;
	}
	return (1);
}

char	**parse_cmd(const char *cmd, int start, int end, int count)
{
	int		i;
	char	**c;

	while (set_start_end(&start, &end, cmd, 0))
		count++;
	start = 0;
	end = 0;
	i = 0;
	c = malloc(sizeof(char *) * (count + 1));
	if (!c)
		return (perror("malloc"), NULL);
	while (set_start_end(&start, &end, cmd, 0))
	{
		if (cmd[start] == '"' || cmd[start] == 39)
			c[i] = trim_str(ft_substr(cmd, start + 1, end - start - 2), 0, 0,
					0);
		else
			c[i] = trim_str(ft_substr(cmd, start, end - start), 0, 0, 0);
		if (!c[i])
			return (perror("malloc"), free_return(c, i));
		i++;
	}
	c[i] = NULL;
	return (c);
}

char	**split_cmd(char *cmd)
{
	int		i;
	char	**c;

	i = 0;
	if (!ft_strchr(cmd, 39) && !ft_strchr(cmd, 34))
	{
		c = ft_split(cmd, ' ');
		if (!c)
			return (perror("malloc"), NULL);
		return (c);
	}
	if (valid_syntax(cmd))
		return (parse_cmd(cmd, 0, 0, 0));
	else
		return (ft_putstr_fd("syntax error: unclosed quote\n", 2), NULL);
}
