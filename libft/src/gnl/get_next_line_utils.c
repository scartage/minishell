/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:48:59 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/26 20:44:38 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

void	my_memmove(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*str_free(t_string *builder)
{
	if (!builder)
		return (NULL);
	free(builder->buffer);
	free(builder);
	return (NULL);
}

t_string	*str_new(void)
{
	t_string	*new_;

	new_ = malloc(sizeof(t_string));
	if (!new_)
		return (NULL);
	new_->buffer = malloc(INTERNAL_BUFFER + 1);
	if (!new_->buffer)
	{
		free(new_);
		return (NULL);
	}
	new_->buffer[0] = 0;
	new_->current = 0;
	new_->size = INTERNAL_BUFFER;
	return (new_);
}

/**
 * @brief Expand the current string to have at least space for new size
 *
 * @param string	The string under expansion
 * @param new_size	The amount of information the string should have
 *
 * @return int		A flag that signals if everything went ok. Returns -1 if it
 * 					failed a malloc, 1 otherwise.
 */
int	expand(t_string *string, ssize_t new_size)
{
	ssize_t	total;
	char	*temp;

	if (new_size < (long)string->size)
		return (BUILDER_OK);
	total = string->size * 2;
	while (new_size > total)
		total *= 2;
	temp = string->buffer;
	string->buffer = malloc(total + 1);
	if (string->buffer == NULL)
	{
		free(temp);
		return (BUILDER_ERROR);
	}
	string->size = total;
	my_memmove(string->buffer, temp, string->current + 1);
	string->buffer[string->current] = 0;
	free(temp);
	return (BUILDER_OK);
}

/**
 * @brief Appends new to the current buffer. If there is not enough space it
 * will double the buffer size and copy the string
 *
 * @param string	The autoexpansive string that will handle a random value size
 * @param new		The new chars to add to the buffer
 * @param new_size	The number of chars to add to the string
 *
 * @return int		A flag that signals if everything went ok. Returns -1 if it
 * 					failed a malloc, 1 otherwise.
 */
int	str_append(t_string *string, char *new)
{
	size_t	len;

	if (string == NULL)
		return (BUILDER_ERROR);
	if (new == NULL)
		return (BUILDER_OK);
	len = 0;
	while (new[len])
		len++;
	if (expand(string, string->current + len) == BUILDER_ERROR)
		return (BUILDER_ERROR);
	my_memmove(string->buffer + string->current, new, len + 1);
	string->current += len;
	string->buffer[string->current] = 0;
	return (BUILDER_OK);
}
