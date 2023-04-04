/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:47:03 by fsoares-          #+#    #+#             */
/*   Updated: 2022/06/01 16:54:04 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include "../../libft.h"

# define __PF_ERROR -1

# define __PF_OPTIONS "-0# +."
# define __PF_MINUS 1
# define __PF_ZERO  2
# define __PF_HASH  4
# define __PF_SPACE 8
# define __PF_PLUS  16
# define __PF_DOT   32

typedef struct s_flags
{
	int		flags;
	int		width;
	int		precision;
	char	format;
}	t_flags;

t_flags	*new_flags(void);
int		has_flag(t_flags *flags, int flag_id);
char	*get_flags(const char *format, t_flags *flags);

int		base_print(t_flags *flags, char *str, int len);

int		to_base(char *str, long n, char *base_str, bool is_unsigned);
int		add_zeros(char **string, int size, int width);
void	add_0s_precision(char *result, char**string, int size, int precision);
int		handle_precision(char **string, int size, int precision);
int		handle_sign(char **string, int size, char sign);
int		add_0x(t_flags *flags, char**string, int size, bool is_zero);

int		print_pointer(t_flags *flags, void *ptr);
int		print_integer(t_flags *flags, int value);
int		print_unsigned(t_flags *flags, unsigned int value);
int		print_hex(t_flags *flags, int value, char format);
int		print_char(t_flags *flags, char c);
int		print_string(t_flags *flags, char *str);

#endif
