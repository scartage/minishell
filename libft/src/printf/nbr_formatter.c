/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_formatter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:14:10 by fsoares-          #+#    #+#             */
/*   Updated: 2022/06/01 16:54:21 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	add_zeros(char **string, int size, int width)
{
	char	*temp;

	if (size >= width || size == __PF_ERROR)
		return (size);
	temp = malloc(width + 10);
	if (!temp)
		return (__PF_ERROR);
	ft_memset(temp, '0', width);
	if (!ft_isalnum(*string[0]))
	{
		temp[0] = **string;
		ft_strlcpy(temp + width - size + 1, *string + 1, size);
	}
	else
		ft_strlcpy(temp + width - size, *string, size + 1);
	free(*string);
	*string = temp;
	return (width);
}

void	add_0s_precision(char *result, char**string, int size, int precision)
{
	ft_memset(result, '0', precision);
	if (!ft_isalnum(*string[0]))
	{
		result[0] = **string;
		ft_strlcpy(result + precision - size + 2, *string + 1, size);
	}
	else
		ft_strlcpy(result + precision - size, *string, size + 1);
}

int	handle_precision(char **string, int size, int precision)
{
	char	*result;

	if (precision == 0 && **string == '0')
		return (0);
	if (precision == 0 && !ft_isalnum(**string) && (*string)[1] == '0')
		return (1);
	if (size == -1 || (size > precision && !ft_isalnum(**string))
		|| (size >= precision && ft_isalnum(**string)))
		return (size);
	result = malloc(precision + 10);
	if (!result)
		return (__PF_ERROR);
	add_0s_precision(result, string, size, precision);
	size = precision;
	if (!ft_isalnum(result[0]))
		size++;
	free(*string);
	*string = result;
	return (size);
}

int	handle_sign(char **string, int size, char sign)
{
	if (size == __PF_ERROR || **string == '-')
		return (size);
	ft_memmove(*string + 1, *string, size + 1);
	**string = sign;
	return (size + 1);
}

int	add_0x(t_flags *flags, char**string, int size, bool is_zero)
{
	int	offset;

	if (size == __PF_ERROR || is_zero)
		return (size);
	offset = 2;
	if (has_flag(flags, __PF_ZERO) && !has_flag(flags, __PF_DOT)
		&& **string == '0')
		offset = 1;
	if (has_flag(flags, __PF_ZERO) && !has_flag(flags, __PF_DOT)
		&& ft_strncmp(*string, "00", 2) == 0)
		offset = 0;
	ft_memmove(*string + offset, *string, size + 1);
	**string = '0';
	(*string)[1] = 'x';
	if (flags->format == 'X')
		(*string)[1] = 'X';
	return (size + offset);
}
