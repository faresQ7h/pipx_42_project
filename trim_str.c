/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 01:10:25 by farmoham          #+#    #+#             */
/*   Updated: 2025/09/17 02:28:02 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

int	trimmed_len(char *str, int i, int count)
{
	int	in_q;
	int	open_q;

	in_q = 0;
	while (str[i])
	{
		if (!in_q && (str[i] == '"' || str[i] == 39))
		{
			open_q = i;
			in_q = 1;
		}
		else if (in_q && (str[i] == str[open_q]))
			in_q = 0;
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
	new_str = malloc(trimmed_len(str, 0, 0) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (!in_q && (str[i] == '"' || str[i] == 39))
		{
			open_q = i;
			in_q = 1;
		}
		else if (in_q && (str[i] == str[open_q]))
			in_q = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (free(str), new_str);
}
