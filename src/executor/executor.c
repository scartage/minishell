/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 20:23:33 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

#include "executor.h"
#include "minishell.h"
#include "../builtins/builtins.h"
#include "../errors/errors.h"
#include "path_handler.h"
#include "pipe_handler.h"
#include "../signals/signals.h"

char	**comm_to_args(t_command *comm);
char	**envs_to_array(t_list *envs);
void	create_heredocs(t_list *commands);
void	delete_heredocs(void);
void	do_exec_call(t_command *comm, t_list *envs, int last_status);
int		handle_wait_pid(int child_pid);
int		execute_single_command(t_command *cmd, t_list *envs, int last_status);

int	execute_first_command(t_command *comm, t_list *envs,
		int out_pipe[2], int last_status)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		setup_first_read_fd(comm);
		setup_pipe_write(comm, out_pipe);
		do_exec_call(comm, envs, last_status);
	}
	return (child_pid);
}

int	execute_last_command(t_command *comm, t_list *envs,
		int in_pipe[2], int last_status)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		setup_pipe_read(comm, in_pipe);
		setup_last_write_fd(comm);
		do_exec_call(comm, envs, last_status);
	}
	return (child_pid);
}

int	exec_command(t_command *comm, t_list *envs, int *pipes[2], int last_status)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		abort_perror("Forking for program");
	if (child_pid == 0)
	{
		setup_pipe_read(comm, pipes[0]);
		setup_pipe_write(comm, pipes[1]);
		do_exec_call(comm, envs, last_status);
	}
	return (child_pid);
}

int	execute_all_commands(t_list *commands, t_list *envs, int last_status)
{
	int	out_pipe[2];
	int	in_pipe[2];
	int	*pipes[2];
	int	child_pid;
	int	status;

	pipe(in_pipe);
	execute_first_command(commands->content, envs, in_pipe, last_status);
	commands = commands->next;
	while (commands && commands->next)
	{
		pipe(out_pipe);
		pipes[0] = in_pipe;
		pipes[1] = out_pipe;
		exec_command(commands->content, envs, pipes, last_status);
		close_pipe(in_pipe);
		in_pipe[0] = out_pipe[0];
		in_pipe[1] = out_pipe[1];
		commands = commands->next;
	}
	child_pid = execute_last_command(commands->content,
			envs, in_pipe, last_status);
	close_pipe(in_pipe);
	status = handle_wait_pid(child_pid);
	return (status);
}

int	execute(t_list *commands, t_list *envs, int last_status)
{
	int	result;

	create_heredocs(commands);
	if (ft_lstsize(commands) == 1)
		result = execute_single_command(commands->content, envs, last_status);
	else
		result = execute_all_commands(commands, envs, last_status);
	delete_heredocs();
	return (result);
}
