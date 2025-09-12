/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:43:05 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/06/02 02:01:27 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	digits_num(unsigned int n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_utoa(unsigned int n)
{
	int		i;
	char	*str;

	i = digits_num(n) + 1;
	str = malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	str[--i] = '\0';
	i--;
	if (!n)
		str[0] = '0';
	while (n)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (str);
}
