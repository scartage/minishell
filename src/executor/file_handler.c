/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:48:59 by fsoares-          #+#    #+#             */
/*   Updated: 2023/09/27 19:44:11 by fsoares-         ###   ########.fr       */
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

	DEBUG("out_file_path: %s\n", path);
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

// by default if no input file is found return the stdin.
int		get_file_input_fd(t_command *comm, int in_pipe)
{
	// FIXME: open the others like it is done by bash
	t_list *file_node = ft_lstlast(comm->input_files);
	if (file_node == NULL)
		return (in_pipe);
	else
	{
		close(in_pipe);
		return (open_read_perm(((t_in_file *)file_node->content)->name));
	}
}

int		get_file_output_fd(t_command *comm, int out_pipe) {
	// FIXME: open the others like it is done by bash
	t_list *file_node = ft_lstlast(comm->output_files);
	if (file_node == NULL)
		return (out_pipe);
	else 
	{
		close(out_pipe);
		t_out_file *file = (t_out_file *)file_node->content;
		return (open_write_perm(file->name, file->type == APPEND));
	}
}

void	setup_pipes(t_command *comm, int in_pipe[2], int out_pipe[2])
{
	(void)comm;
	
	if (dup2(get_file_input_fd(comm, in_pipe[0]), STDIN_FILENO) == -1)
		abort_perror("Redirecting read end of input pipe to stdin");
	if (dup2(get_file_output_fd(comm, out_pipe[1]), STDOUT_FILENO) == -1)
		abort_perror("Redirecting stdout to write end of output pipe");
	if (close(in_pipe[1]) == -1)
		abort_perror("Closing write end of input pipe");
	if (close(out_pipe[0]) == -1)
		abort_perror("Closing read end of output pipe");
}

void	close_pipe(int pipe[2])
{
	if (close(pipe[0]) == -1)
		abort_perror("Closing the read end of the pipe");
	if (close(pipe[1]) == -1)
		abort_perror("Closing the write end of the pipe");
}
