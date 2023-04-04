/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:31:25 by fsoares-          #+#    #+#             */
/*   Updated: 2022/03/04 16:48:35 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_flags *flags, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (base_print(flags, str, 1));
}

int	print_string(t_flags *flags, char *str)
{
	char	null_str[10];
	int		len;

	if (str == NULL)
	{
		ft_strlcpy(null_str, "(null)", 7);
		str = null_str;
	}
	len = ft_strlen(str);
	if (has_flag(flags, __PF_DOT))
	{
		if (flags->precision < len)
			len = flags->precision;
	}
	return (base_print(flags, str, len));
}
