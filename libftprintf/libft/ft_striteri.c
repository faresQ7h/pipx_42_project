/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:36:42 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/05/26 04:47:54 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// s: The string to iterate over.
// f: The function to apply to each character

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
