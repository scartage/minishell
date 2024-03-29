/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:32:17 by scartage          #+#    #+#             */
/*   Updated: 2023/11/11 17:06:23 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>		// para erno
#include <limits.h>

static long	handle_overflow(int sign)
{
	errno = ERANGE;
	if (sign == -1)
		return (LONG_MIN);
	else
		return (LONG_MAX);
}

static long	ft_strtol(const char *str, char **endptr)
{
	long	result;
	int		sign;
	int		digit;

	sign = get_sign(&str);
	result = 0;
	while (*str == ' ')
		str++;
	if (sign == -1 && ft_strncmp(str, "9223372036854775808", 19) == 0)
	{
		if (endptr)
			*endptr = (char *)(str + 19);
		return (LONG_MIN);
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (handle_overflow(sign));
		result = result * 10 + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

static int	is_valid_number(char *str)
{
	char	*endptr;
	long	num;

	errno = 0;
	num = ft_strtol(str, &endptr);
	if (errno == ERANGE || *endptr != '\0' || str == endptr)
		return (1);
	return (0);
}

static int	check_all_numbers(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (i == 0 || !ft_isdigit(str[i - 1]))
		return (1);
	return (0);
}

int	ft_isdigit_void(char *str)
{
	int	i;

	i = 0;
	str = ft_strtrim(str, " ");
	if (ft_strncmp(str, "--", 3) == 0)
	{
		free(str);
		return (0);
	}
	if (check_all_numbers(str) == 1)
	{
		free(str);
		return (1);
	}
	if (ft_strlen(str) >= 18)
	{
		i = is_valid_number(str);
		if (i == 1)
		{
			free(str);
			return (1);
		}
	}
	free(str);
	return (0);
}
