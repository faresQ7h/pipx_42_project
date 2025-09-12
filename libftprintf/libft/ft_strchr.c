/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:03:34 by farmoham          #+#    #+#             */
/*   Updated: 2025/05/25 01:00:43 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int search_str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == search_str)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == search_str)
		return ((char *)&str[i]);
	return (NULL);
}
