/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:33:06 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/12 18:03:23 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file_handler.h"
#include "../errors/errors.h"

void	setup_first_read_fd(t_command *command)
{
	int	in_fd;

	in_fd = get_input_fd(command->input_files);
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
}

void	setup_last_write_fd(t_command *command)
{
	int	out_fd;

	out_fd = get_output_fd(command->output_files);
	if (out_fd != 0)
		dup2(out_fd, STDOUT_FILENO);
}

void	setup_pipe_read(t_command *command, int in_pipe[2])
{
	int	in_fd;

	in_fd = get_input_fd(command->input_files);
	if (in_fd == 0)
		dup2(in_pipe[0], STDIN_FILENO);
	else
	{
		close(in_pipe[0]);
		dup2(in_fd, STDIN_FILENO);
	}
	close(in_pipe[1]);
}

void	setup_pipe_write(t_command *command, int out_pipe[2])
{
	int	out_fd;

	out_fd = get_output_fd(command->output_files);
	if (out_fd == 0)
		dup2(out_pipe[1], STDOUT_FILENO);
	else
	{
		close(out_pipe[1]);
		dup2(out_fd, STDOUT_FILENO);
	}
	close(out_pipe[0]);
}

void	close_pipe(int pipe[2])
{
	if (close(pipe[0]) == -1)
		abort_perror("Closing the read end of the pipe");
	if (close(pipe[1]) == -1)
		abort_perror("Closing the write end of the pipe");
}
