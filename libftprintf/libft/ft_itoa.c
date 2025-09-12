/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:08:43 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/05/26 00:37:43 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	digits_num(int n)
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

static int	write_in_index(int sign, int i, int n, char *str)
{
	if (sign == -1)
		str[i] = '0' + (-(n % 10));
	else
		str[i] = '0' + (n % 10);
	return (n / 10);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		i;
	char	*str;

	i = 0;
	sign = 1;
	if (n < 0)
		sign = -1;
	if (sign == -1)
		str = malloc((i = (digits_num(n) + 2)) * sizeof(char));
	else
		str = malloc((i = digits_num(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[--i] = '\0';
	i--;
	if (!n)
		str[0] = '0';
	while (n)
		n = write_in_index(sign, (i)--, n, str);
	if (sign == -1)
		str[0] = '-';
	return (str);
}
