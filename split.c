/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:06:45 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/18 00:41:40 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

void	*free_return(char **cmd, int cmd_len)
{
	int	i;

	i = 0;
	while (i < cmd_len)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (NULL);
}

int	which_case(const char *cmd, int *in_q, int *last_q, int *i)
{
	if (cmd[*i])
	{
		if (!*in_q && cmd[*i] == '\\')
			(*i)++;
		else if (!*in_q && (cmd[*i] == '"' || cmd[*i] == '\''))
		{
			(*last_q) = (*i);
			(*in_q) = 1;
		}
		else if (*in_q && cmd[*i] == '\\' && cmd[*last_q] == '"')
		{
			(*i)++;
			if (cmd[*i] && (cmd[*i] == '"' || cmd[*i] == '\\' || cmd[*i] == '`'
					|| cmd[*i] == '$'))
				(*i)++;
			return (1);
		}
		else if (*in_q && cmd[(*i)] == cmd[(*last_q)])
			(*in_q) = 0;
		if (cmd[(*i)])
			(*i)++;
		return (1);
	}
	return (0);
}

int	set_start_end(int *start, int *end, const char *cmd, int in_q)
{
	int	open_q;

	*start = *end;
	while (cmd[*start] && (cmd[*start] == ' '))
		(*start)++;
	if (!cmd[*start])
		return (0);
	if ((cmd[*start] == '"' || cmd[*start] == '\''))
	{
		open_q = *start;
		in_q = 1;
	}
	*end = (*start) + 1;
	while (cmd[*end] && (cmd[*end] != ' ' || in_q))
		which_case(cmd, &in_q, &open_q, end);
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
	int		in_q;
	int		last_q;
	char	**c;

	if (!ft_strchr(cmd, '\'') && !ft_strchr(cmd, '"') && !ft_strchr(cmd, '\\'))
	{
		c = ft_split(cmd, ' ');
		if (!c)
			return (perror("malloc"), NULL);
		return (c);
	}
	i = 0;
	in_q = 0;
	last_q = 0;
	while (which_case(cmd, &in_q, &last_q, &i))
		;
	if (in_q == 0)
		return (parse_cmd(cmd, 0, 0, 0));
	else
		return (ft_putstr_fd("syntax error: unclosed quote\n", 2), NULL);
}
