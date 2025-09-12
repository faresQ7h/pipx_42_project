/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:50:21 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/05/25 02:11:16 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	i;

	if (!nitems || !size)
		return (malloc(1));
	ptr = malloc(nitems * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < (nitems * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
