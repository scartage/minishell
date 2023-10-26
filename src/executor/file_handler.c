/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:48:59 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/26 21:20:48 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "../errors/errors.h"
#include "file_handler.h"

int	open_read_perm(char *path)
{
	int		fd;

	if (access(path, F_OK) == -1)
		abort_perror(path);
	if (access(path, R_OK) == -1)
		abort_perror(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		abort_perror(path);
	return (fd);
}

int	open_write_perm(char *path, bool is_append)
{
	int	fd;

	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		abort_perror(path); //FIXME
	if (is_append)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		abort_perror(path);
	return (fd);
}

int	get_input_fd(t_list *in_files)
{
	t_in_file	*in_file;

	if (in_files == NULL)
		return (0);
	while (in_files->next && in_files->next->next)
	{
		// FIXME: handle it the same way as bash for multiple inputs
		in_files = in_files->next;
	}
	in_file = in_files->content;
	return (open_read_perm(in_file->name));
}

int	get_output_fd(t_list *out_files)
{
	t_out_file	*out_file;

	if (out_files == NULL)
		return (0);
	while (out_files->next && out_files->next->next)
	{
		// FIXME: handle it the same way as bash for multiple outputs
		out_files = out_files->next;
	}
	out_file = out_files->content;
	return (open_write_perm(out_file->name, out_file->type == APPEND));
}
