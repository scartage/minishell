/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:48:59 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/04 20:11:08 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "../errors/errors.h"
#include "file_handler.h"
#include "path_handler.h"

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

	if (is_directory(path))
	{
		show_error(path, "Is a directory");
		exit(1);
	}
	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		abort_perror(path);
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
	while (in_files->next)
	{
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
	while (out_files->next)
	{
		out_file = out_files->content;
		close(open_write_perm(out_file->name, out_file->type == APPEND));
		out_files = out_files->next;
	}
	out_file = out_files->content;
	return (open_write_perm(out_file->name, out_file->type == APPEND));
}
