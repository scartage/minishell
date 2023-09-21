/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:48:59 by fsoares-          #+#    #+#             */
/*   Updated: 2023/09/21 19:44:26 by fsoares-         ###   ########.fr       */
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

int	open_write_perm(char *path, bool is_heredoc)
{
	int	fd;

	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		abort_perror(path);
	if (is_heredoc)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		abort_perror(path);
	return (fd);
}

void	setup_pipes(t_command *comm, int in_pipe[2], int out_pipe[2])
{
	(void)comm;
	// FIXME: add the file handling
	if (dup2(in_pipe[0], STDIN_FILENO) == -1)
		abort_perror("Redirecting read end of input pipe to stdin");
	if (dup2(out_pipe[1], STDOUT_FILENO) == -1)
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
