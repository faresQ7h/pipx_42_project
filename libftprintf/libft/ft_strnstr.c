/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:20:51 by farmoham          #+#    #+#             */
/*   Updated: 2025/05/26 17:59:54 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	is_matching(const char *big, const char *little, size_t len,
		size_t last)
{
	int	i;

	i = 0;
	while (little[i] && big[i] && last < len)
	{
		if (big[i] != little[i])
			return (0);
		last++;
		i++;
	}
	return (little[i] == '\0');
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	last;

	if ((!little || !big) && len == 0)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	last = 0;
	while (big[last] && last < len)
	{
		if (big[last] == little[0])
		{
			if (is_matching(&((char *)big)[last], &little[0], len, last))
				return (((char *)big) + last);
		}
		last++;
	}
	return (NULL);
}
