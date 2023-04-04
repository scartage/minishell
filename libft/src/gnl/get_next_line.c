/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:49:07 by fsoares-          #+#    #+#             */
/*   Updated: 2022/03/04 16:53:09 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

typedef struct s_buffer	t_buffer;
struct s_buffer {
	char		*buffer;
	int			fd;
	t_buffer	*next;
};

char	*get_buffer_for_fd(t_buffer **buffers, int fd)
{
	t_buffer	*temp;

	temp = *buffers;
	while (temp != NULL)
	{
		if (fd == temp->fd)
			return (temp->buffer);
		temp = temp->next;
	}
	temp = malloc(sizeof(t_buffer));
	if (!temp)
		return (NULL);
	temp->buffer = malloc(BUFFER_SIZE + 1);
	if (!temp->buffer)
	{
		free(temp);
		return (NULL);
	}
	temp->fd = fd;
	temp->next = *buffers;
	temp->buffer[0] = 0;
	*buffers = temp;
	return (temp->buffer);
}

char	*delete_objects(t_buffer **buffers, t_string *builder, int fd)
{
	t_buffer	*temp;
	t_buffer	*prev;

	free_builder(builder);
	temp = *buffers;
	prev = NULL;
	while (temp != NULL)
	{
		if (temp->fd == fd)
		{
			free(temp->buffer);
			if (prev == NULL)
				*buffers = temp->next;
			else
				prev->next = temp->next;
			free(temp);
			return (NULL);
		}
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}

int	get_newline_offset(char *buffer)
{
	int	n;

	n = 0;
	while (buffer[n])
	{
		if (buffer[n] == '\n')
			return (n);
		n++;
	}
	return (-1);
}

char	*build_res(t_string *builder, char *buffer, int b_size, int bytes)
{
	char	*res;
	int		len;

	if ((b_size == 0 && bytes == 0 && builder->current == 0)
		|| builder == NULL || buffer == NULL)
		return (NULL);
	res = malloc(builder->current + b_size + 1);
	if (!res)
		return (NULL);
	my_memmove(res, builder->buffer, builder->current);
	my_memmove(res + builder->current, buffer, b_size);
	res[builder->current + b_size] = 0;
	len = 0;
	while (buffer[len])
		len++;
	len = len - b_size + 1;
	my_memmove(buffer, buffer + b_size, len);
	buffer[len] = 0;
	free_builder(builder);
	return (res);
}

char	*get_next_line(int fd)
{
	static t_buffer	*buffers;
	ssize_t			bytes;
	t_string		*builder;
	int				offset;
	char			*buffer;

	bytes = 1;
	builder = new_builder();
	buffer = get_buffer_for_fd(&buffers, fd);
	while (bytes > 0 && buffer)
	{
		offset = get_newline_offset(buffer);
		if (offset != -1)
			break ;
		if (append_string(builder, buffer) == BUILDER_ERROR)
			return (delete_objects(&buffers, builder, fd));
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (delete_objects(&buffers, builder, fd));
		buffer[bytes] = 0;
	}
	buffer = build_res(builder, buffer, offset + 1, bytes);
	if (buffer == NULL)
		delete_objects(&buffers, builder, fd);
	return (buffer);
}
