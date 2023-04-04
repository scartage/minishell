/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:58:28 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/04 18:49:00 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl/get_next_line.h"

int	expand(t_string *string, ssize_t new_size);

int	append_char(t_string *string, char new)
{
	if (expand(string, string->current + 1) == BUILDER_ERROR)
		return (BUILDER_ERROR);
	string->buffer[string->current] = new;
	string->current++;
	string->buffer[string->current] = 0;
	return (BUILDER_OK);
}
