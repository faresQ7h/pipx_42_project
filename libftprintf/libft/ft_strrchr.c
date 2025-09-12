/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:36:39 by farmoham          #+#    #+#             */
/*   Updated: 2025/05/25 01:01:32 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *str, int search_str)
{
	int		i;
	char	*last;

	last = NULL;
	i = 0;
	while (1)
	{
		if (str[i] == search_str)
			last = (char *)&str[i];
		if (!str[i])
			break ;
		i++;
	}
	return (last);
}
