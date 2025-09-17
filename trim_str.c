/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 01:10:25 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/18 00:36:24 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

void	handel_backslash(char *str, int *i, int *count)
{
	(*i)++;
	if (!(str[*i] == '"' || str[*i] == '\\' || str[*i] == '`'
			|| str[*i] == '$'))
		(*count)++;
}

int	set_i(const char *str, int *in_q, int *open_q, int *i)
{
	if (!str[*i])
		return (0);
	if (!*in_q && str[*i] == '\\' && str[*i + 1])
		(*i)++;
	else if (!*in_q && (str[*i] == '"' || str[*i] == '\''))
	{
		*open_q = *i;
		*in_q = 1;
		return (0);
	}
	else if (*in_q && str[*i] == '\\' && str[*open_q] == '"' && str[*i + 1])
	{
		if ((str[*i + 1] == '"' || str[*i + 1] == '\\' || str[*i + 1] == '`'
				|| str[*i + 1] == '$'))
			(*i)++;
	}
	else if (*in_q && str[*i] == str[*open_q])
	{
		*in_q = 0;
		return (0);
	}
	return (1);
}

int	trimmed_len(char *str, int i, int in_q, int count)
{
	int	open_q;

	while (str[i])
	{
		if (!in_q && str[i] == '\\' && str[i + 1])
			i++;
		else if (!in_q && (str[i] == '"' || str[i] == '\''))
		{
			open_q = i;
			in_q = 1;
			i++;
			continue ;
		}
		else if (in_q && str[i] == '\\' && str[open_q] == '"' && str[i + 1])
			handel_backslash(str, &i, &count);
		else if (in_q && str[(i)] == str[open_q])
		{
			in_q = 0;
			i++;
			continue ;
		}
		i++;
		count++;
	}
	return (count);
}

char	*trim_str(char *str, int i, int j, int in_q)
{
	int		open_q;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = malloc(trimmed_len(str, 0, 0, 0) + 1);
	if (!new_str)
		return (free(str), NULL);
	in_q = 0;
	while (str[i])
	{
		if (set_i(str, &in_q, &open_q, &i))
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}
