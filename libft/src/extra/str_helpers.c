/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:58:28 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 17:02:24 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl/get_next_line.h"
#include <stdlib.h>

int	expand(t_string *string, ssize_t new_size);

int	str_add_char(t_string *string, char new)
{
	if (expand(string, string->current + 1) == BUILDER_ERROR)
		return (BUILDER_ERROR);
	string->buffer[string->current] = new;
	string->current++;
	string->buffer[string->current] = 0;
	return (BUILDER_OK);
}

int	str_add_int(t_string *string, int number)
{
	char	*number_str;

	number_str = ft_itoa(number);
	str_append(string, number_str);
	free(number_str);
	return (BUILDER_OK);
}

void	str_clear(t_string *string)
{
	string->current = 0;
	string->buffer[0] = 0;
}

char	*str_to_chars(t_string *string)
{
	char	*to_return;

	to_return = ft_strdup(string->buffer);
	str_free(string);
	return (to_return);
}
