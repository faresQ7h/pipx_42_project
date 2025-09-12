/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:18:02 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/08/21 18:48:44 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	continue_specifier(const char *str, va_list args, int *count, int *i);

int	valid_specifier(const char *ptr)
{
	char	*ok_species;
	int		i;

	i = 0;
	ok_species = "cspdiuxX%";
	while (ptr[1] && ok_species[i])
	{
		if (ptr[1] == ok_species[i])
			return (1);
		i++;
	}
	return (0);
}

void	print_string(const char *ptr, int *count)
{
	int	i;

	if (!ptr)
	{
		*count += 6;
		write(1, "(null)", 6);
		return ;
	}
	i = 0;
	while (ptr[i])
	{
		write(1, &ptr[i], 1);
		i++;
	}
	*count += i;
}

void	print_hex_address(uintptr_t x, int *count)
{
	uintptr_t	reminder;
	char		*hex_digits;

	hex_digits = "0123456789abcdef";
	if (!x)
	{
		write(1, "0x", 2);
		*count += 2;
		return ;
	}
	reminder = x % 16;
	print_hex_address(x /= 16, count);
	write(1, &hex_digits[reminder], 1);
	(*count)++;
}

void	do_specifier(const char *str, va_list args, int *count, int *i)
{
	char	c;
	void	*ptr;

	if (str[*i] == 'c')
	{
		c = (char)va_arg(args, int);
		write(1, &c, 1);
		(*count)++;
	}
	else if (str[*i] == 's')
		print_string(va_arg(args, char *), count);
	else if (str[*i] == 'p')
	{
		ptr = va_arg(args, void *);
		if (!ptr)
			print_string("(nil)", count);
		else
			print_hex_address((uintptr_t)ptr, count);
	}
	else
		continue_specifier(str, args, count, i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && valid_specifier(&str[i]))
		{
			i++;
			do_specifier(str, args, &count, &i);
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
