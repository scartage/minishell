/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:41:23 by fsoares-          #+#    #+#             */
/*   Updated: 2022/03/04 16:48:08 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

/**
 * @brief Creates an empty flags structure
 *
 * @return t_flags* The created structure
 */
t_flags	*new_flags(void)
{
	t_flags	*flags;

	flags = malloc(sizeof(t_flags));
	if (flags == NULL)
		return (NULL);
	flags->flags = 0;
	flags->width = -1;
	flags->precision = -1;
	flags->format = 0;
	return (flags);
}

/**
 * @brief Checks if a flag (or a combination) are active
 *
 * @param flags		The structure to check against
 * @param flag_id	The id of the flag (from `libft.h`)
 * @return int
 */
int	has_flag(t_flags *flags, int flag_id)
{
	return (flags->flags & flag_id);
}

/**
 * @brief Parses the flag information and saves it in the `flags` parameter
 *
 * @param format	The format string, pointed to the next char after the %
 * @param flags		The structure where the flags information will be saved
 * @return char*	The pointer to where in format the format specifier is.
 * 					Meaning one of the following: cspdiuxX%
 */
char	*get_flags(const char *format, t_flags *flags)
{
	char	*temp;
	char	*options;

	temp = (char *)format;
	options = __PF_OPTIONS;
	while (temp)
	{
		temp = ft_memchr(options, *format, 5);
		if (temp)
		{
			flags->flags |= 1 << (temp - options);
			format++;
		}
	}
	flags->width = ft_atoi(format);
	while (ft_isdigit(*format))
		format++;
	if (*format != '.')
		return ((char *)format);
	flags->flags |= __PF_DOT;
	flags->precision = ft_atoi(++format);
	while (ft_isdigit(*format))
		format++;
	return ((char *)format);
}
