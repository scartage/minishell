/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:47:23 by fsoares-          #+#    #+#             */
/*   Updated: 2022/05/13 15:36:37 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

/**
 * @brief Writes the string to the output
 *
 * @param total	The current count of printed chars
 * @param str	The string to print
 * @param len	The length of the string
 * @return int	The new total. Or if there is an error, -1
 */
int	write_string(int total, char *str, int len)
{
	ssize_t	temp;

	if (total == __PF_ERROR)
		return (__PF_ERROR);
	temp = write(STDOUT_FILENO, str, len);
	if (temp == __PF_ERROR)
		return (__PF_ERROR);
	return (total + temp);
}

/**
 * @brief Writes `width - len` spaces
 *
 * @param total	The total of characters printed until now
 * @param width	The desired width of the total string
 * @param len	The len of the information (not spaces) what will be printed
 * @return int	The new total. Or if there is an error, -1
 */
int	print_spaces(int total, int width, int len)
{
	char	buffer[256];
	char	*temp;
	int		spaces;

	if (total == __PF_ERROR || width <= len)
		return (total);
	spaces = width - len;
	if (spaces < 256)
		temp = buffer;
	else
	{
		temp = malloc(spaces + 1);
		if (!temp)
			return (__PF_ERROR);
	}
	temp[spaces] = 0;
	ft_memset(temp, ' ', spaces);
	spaces = write_string(total, temp, spaces);
	if (temp != buffer)
		free(temp);
	return (spaces);
}

/**
 * @brief It will print the string into the output taking into account which
 * 	      flags are set and adjusting the printed information accordingly
 *
 * @param flags The flags that were set for this value
 * @param str	The string to be printed
 * @param len	The length of the string to be printed
 * @return int  The total of characters printed, or -1 if there was an error
 */
int	base_print(t_flags *flags, char *str, int len)
{
	int	total;

	if (len == __PF_ERROR)
		return (__PF_ERROR);
	total = 0;
	if (has_flag(flags, __PF_MINUS))
	{
		total = write_string(total, str, len);
		total = print_spaces(total, flags->width, len);
	}
	else
	{
		total = print_spaces(total, flags->width, len);
		total = write_string(total, str, len);
	}
	return (total);
}
