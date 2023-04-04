/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:49:37 by fsoares-          #+#    #+#             */
/*   Updated: 2022/06/01 16:55:15 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	apply_flags(t_flags *flags, char **nbr_str, int size)
{
	bool	is_zero;

	is_zero = (**nbr_str == '0');
	if (has_flag(flags, __PF_PLUS))
		size = handle_sign(nbr_str, size, '+');
	if (has_flag(flags, __PF_SPACE))
		size = handle_sign(nbr_str, size, ' ');
	if (has_flag(flags, __PF_DOT))
		size = handle_precision(nbr_str, size, flags->precision);
	if (has_flag(flags, __PF_ZERO) && !has_flag(flags, __PF_DOT))
		size = add_zeros(nbr_str, size, flags->width);
	if (has_flag(flags, __PF_HASH))
		size = add_0x(flags, nbr_str, size, is_zero);
	return (size);
}

int	print_pointer(t_flags *flags, void *ptr)
{
	char	*result;
	int		size;

	result = malloc(32);
	if (!result)
		return (-1);
	result[0] = '0';
	result[1] = 'x';
	size = to_base(result + 2, (long)ptr, "0123456789abcdef", true) + 2;
	size = apply_flags(flags, &result, size);
	size = base_print(flags, result, size);
	free(result);
	return (size);
}

int	print_integer(t_flags *flags, int value)
{
	char	*result;
	int		size;

	result = malloc(32);
	if (!result)
		return (-1);
	size = to_base(result, value, "0123456789", false);
	size = apply_flags(flags, &result, size);
	size = base_print(flags, result, size);
	free(result);
	return (size);
}

int	print_unsigned(t_flags *flags, unsigned int value)
{
	char	*result;
	int		size;

	result = malloc(32);
	if (!result)
		return (-1);
	size = to_base(result, (unsigned int)value, "0123456789", true);
	size = apply_flags(flags, &result, size);
	size = base_print(flags, result, size);
	free(result);
	return (size);
}

int	print_hex(t_flags *flags, int value, char format)
{
	char	*result;
	int		size;
	char	*base;

	result = malloc(32);
	if (!result)
		return (-1);
	base = "0123456789abcdef";
	if (format == 'X')
		base = "0123456789ABCDEF";
	size = to_base(result, (unsigned int)value, base, true);
	size = apply_flags(flags, &result, size);
	size = base_print(flags, result, size);
	free(result);
	return (size);
}
