/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:19:10 by fsoares-          #+#    #+#             */
/*   Updated: 2022/03/04 18:16:44 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static long	construct_number(int digits[20], int d, int sign)
{
	long	res;
	long	power;

	res = 0;
	power = sign;
	while (--d >= 0)
	{
		res += digits[d] * power;
		power *= 10;
	}
	return (res);
}

long	ft_atol(const char *str)
{
	size_t	i;
	int		sign;
	int		digits[40];
	int		d;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	d = 0;
	while (d < 20 && str[i] && ft_isdigit(str[i]))
		digits[d++] = str[i++] - '0';
	return (construct_number(digits, d, sign));
}
