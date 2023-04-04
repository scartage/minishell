/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:47:31 by fsoares-          #+#    #+#             */
/*   Updated: 2022/07/18 16:07:06 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static const char	*jump(const char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (str + i);
}

static double	parse_dot(const char *str, double temp)
{
	int	i;
	int	exponent;

	i = 0;
	exponent = 0;
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			temp = temp * 10.0 + (str[i] - '0');
			i++;
			exponent--;
		}
	}
	while (exponent < 0)
	{
		temp *= 0.1;
		exponent++;
	}
	return (temp);
}

double	ft_atof(const char *str)
{
	size_t	i;
	int		sign;
	double	result;

	i = 0;
	result = 0;
	str = jump(str, &sign);
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	return (parse_dot(str + i, result) * sign);
}
