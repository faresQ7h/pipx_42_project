/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:32:32 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/05/25 23:05:06 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free_all(char **ptr, int strings)
{
	while (strings >= 0)
	{
		free(ptr[strings]);
		strings--;
	}
	free(ptr);
}

static int	count_strings(const char *s, char c)
{
	int	strings;
	int	new_str;
	int	i;

	strings = 0;
	new_str = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			new_str = 1;
		if (new_str)
		{
			strings++;
			new_str = 0;
			while (s[i] && s[i] != c)
				i++;
		}
		if (s[i] && s[i] == c)
			i++;
	}
	return (strings);
}

static int	set_end(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**set_strings(char **ptr, const char *s, char c, int start)
{
	int	i;
	int	count;
	int	end;

	i = 0;
	count = count_strings(s, c);
	while (i < count)
	{
		while (s[start] && s[start] == c)
			start++;
		end = set_end((char *)s, start, c);
		ptr[i] = (char *)malloc((end - start + 1) * sizeof(char));
		if (!ptr[i])
			return (ft_free_all(ptr, i - 1), NULL);
		ft_strlcpy(ptr[i++], (char *) s + start, end - start + 1);
		start = end;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		start;
	int		count;

	if (!s)
		return (NULL);
	count = count_strings(s, c);
	ptr = (char **)malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	start = 0;
	if (!set_strings(ptr, s, c, start))
		return (NULL);
	return (ptr);
}
