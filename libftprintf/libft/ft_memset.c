/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 04:06:05 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/05/26 06:38:31 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *ptr, int replace, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)ptr)[i] = replace;
		i++;
	}
	return (ptr);
}
