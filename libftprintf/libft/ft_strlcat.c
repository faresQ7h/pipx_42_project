/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 04:30:57 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/05/26 15:20:57 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Save the initial length of dest
// Return the length that would have been created
// Find length of dest (up to dest_size)
// If dest_size == 0 or i >= dest_size, don't write, just return

#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;

	i = 0;
	j = 0;
	while (i < dest_size && dest[i])
		i++;
	dest_len = i;
	while (src[j] && (i + 1) < dest_size)
		dest[i++] = src[j++];
	if (dest_len < dest_size)
		dest[i] = '\0';
	while (src[j])
		j++;
	return (dest_len + j);
}
