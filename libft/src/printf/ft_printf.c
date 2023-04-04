/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:50:21 by fsoares-          #+#    #+#             */
/*   Updated: 2022/09/22 15:16:35 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

int	do_formatting(t_flags *flags, const char **format, va_list args)
{
	char	current;

	*format = get_flags(*format, flags);
	current = **format++;
	flags->format = current;
	if (current == 'c')
		return (print_char(flags, va_arg(args, int)));
	if (current == 's')
		return (print_string(flags, va_arg(args, char *)));
	if (current == 'p')
		return (print_pointer(flags, va_arg(args, void *)));
	if (current == 'd' || current == 'i')
		return (print_integer(flags, va_arg(args, int)));
	if (current == 'u')
		return (print_unsigned(flags, va_arg(args, unsigned int)));
	if (current == 'x' || current == 'X')
		return (print_hex(flags, va_arg(args, unsigned int), current));
	if (current == '%')
		return (print_char(flags, '%'));
	return (__PF_ERROR);
}

int	format_wrapper(const char **format, va_list args)
{
	t_flags	*flags;
	int		result;

	flags = new_flags();
	if (!flags)
		return (-1);
	result = do_formatting(flags, format, args);
	free(flags);
	return (result);
}

static int	internal(const char *format, va_list args)
{
	int		res;
	int		temp;

	res = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			temp = format_wrapper(&format, args);
		}
		else
			temp = write(STDOUT_FILENO, format, 1);
		if (temp == -1)
			return (-1);
		res += temp;
		format++;
	}
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = internal(format, args);
	va_end(args);
	return (res);
}

int	ft_printfln(const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = internal(format, args);
	va_end(args);
	write(1, "\n", 1);
	return (res + 1);
}
