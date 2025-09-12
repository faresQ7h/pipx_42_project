/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:31:59 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/08/21 18:54:34 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	print_string(const char *ptr, int *count);
char	*ft_utoa(unsigned int n);

void	print_hex_number(unsigned int x, int *count, int upper)
{
	int		reminder;
	char	*hex_digits;

	if (upper)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (!x)
	{
		write(1, "0", 1);
		(*count)++;
		return ;
	}
	reminder = x % 16;
	if (!((x / 16) == 0))
		print_hex_number(x /= 16, count, upper);
	write(1, &hex_digits[reminder], 1);
	(*count)++;
}

void	continue_specifier_two(const char *str, va_list args, int *count,
		int *i)
{
	if (str[*i] == 'x')
		print_hex_number(va_arg(args, unsigned int), count, 0);
	else if (str[*i] == 'X')
		print_hex_number(va_arg(args, unsigned int), count, 1);
	else if (str[*i] == '%')
	{
		write(1, "%", 1);
		(*count)++;
	}
}

void	continue_specifier(const char *str, va_list args, int *count, int *i)
{
	char			*ptr;
	unsigned int	n;
	int				x;

	if (str[*i] == 'd' || str[*i] == 'i')
	{
		x = va_arg(args, int);
		ptr = ft_itoa(x);
		if (!ptr)
			return (print_string(NULL, count));
		print_string(ptr, count);
		free(ptr);
	}
	else if (str[*i] == 'u')
	{
		n = va_arg(args, unsigned int);
		ptr = ft_utoa(n);
		print_string(ptr, count);
		free(ptr);
	}
	else
		continue_specifier_two(str, args, count, i);
}
