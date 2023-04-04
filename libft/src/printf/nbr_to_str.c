/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:03:34 by fsoares-          #+#    #+#             */
/*   Updated: 2022/06/01 16:54:41 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_digits(long n, int base, bool is_unsigned)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	if (!is_unsigned && n < 0)
		res++;
	while (n != 0)
	{
		if (is_unsigned)
			n = (unsigned long)n / base;
		else
			n = n / base;
		res++;
	}
	return (res);
}

static char	to_digit(long n, int base, char *base_str, bool is_unsigned)
{
	int	value;

	value = n % base;
	if (value < 0)
		value = -value;
	if (is_unsigned)
		value = (unsigned long)n % base;
	return (base_str[value]);
}

int	get_number_digits(char *str, int size, long n, bool is_unsigned)
{
	int	limit;

	limit = size;
	if (!is_unsigned && n < 0)
	{
		str[0] = '-';
		limit = size - 1;
	}
	return (limit);
}

/**
 * @brief Converts the desired number to a specific base
 *
 * @param str			The memory space to where the number will be written
 * @param n				The value to be converted
 * @param base_str		A string with the desired base
 * @param is_unsigned	A boolean that indicates if the passed number is to
 * 						be treated as an unsigned number
 * @return int			The number of characters saved by this function
 */
int	to_base(char *str, long n, char *base_str, bool is_unsigned)
{
	int	size;
	int	base;
	int	i;
	int	limit;

	base = ft_strlen(base_str);
	size = num_digits(n, base, is_unsigned);
	i = 0;
	limit = get_number_digits(str, size, n, is_unsigned);
	str[size] = 0;
	while (i++ < limit)
	{
		str[size - i] = to_digit(n, base, base_str, is_unsigned);
		if (is_unsigned)
			n = (unsigned long)n / base;
		else
			n = n / base;
	}
	return (size);
}
