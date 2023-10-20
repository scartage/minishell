/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/10/20 21:20:07 by fsoares-         ###   ########.fr       */
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

void	do_exec_call(t_command *comm, t_list *envs)
{
	char		*command_path;
	char		**args;
	char		**envp;
	t_builtin	builtin;
	int			return_code;

	builtin = get_builtin(comm);
	if (builtin.name != NULL)
	{
		return_code = builtin.fn(comm->arguments, envs);
		exit(return_code);
	}
	else
	{
		command_path = get_full_path(comm, envs);
		args = comm_to_args(comm);
		envp = envs_to_array(envs);
		if (execve(command_path, args, envp) == -1)
			abort_perror("Problem executing command");
	}
}

int	handle_wait_pid(int child_pid)
{
	int	status;

	waitpid(child_pid, &status, 0);
	if (WTERMSIG(status) == SIGQUIT)
		printf("Quit: 3\n");
	if (WTERMSIG(status) == SIGINT)
		printf("\n");
	if (WTERMSIG(status) == SIGKILL)
		printf("Killed: 9\n");
	while (wait(NULL) != -1)
		;
	return (WEXITSTATUS(status));
}

int	execute_single_command(t_command *command, t_list *envs)
{
	t_builtin	builtin;
	int			child_pid;
	int			status;

	builtin = get_builtin(command);
	if (builtin.name != NULL)
	{
		int saved_stdin = dup(0);
		int saved_stdout = dup(1);
		setup_first_read_fd(command);
		setup_last_write_fd(command);
		status = builtin.fn(command->arguments, envs);
		dup2(saved_stdout, 1);
		dup2(saved_stdin, 0);
		close(saved_stdout);
		close(saved_stdin);
	}
	else
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			setup_first_read_fd(command);
			setup_last_write_fd(command);
			do_exec_call(command, envs);
		}
		status = handle_wait_pid(child_pid);
	}
	return (status);
}

int	execute_first_command(t_command *comm, t_list *envs, int out_pipe[2])
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		setup_first_read_fd(comm);
		setup_pipe_write(comm, out_pipe);
		do_exec_call(comm, envs);
	}
	return (child_pid);
}

int	execute_last_command(t_command *comm, t_list *envs, int in_pipe[2])
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		setup_pipe_read(comm, in_pipe);
		setup_last_write_fd(comm);
		do_exec_call(comm, envs);
	}
	return (child_pid);
}

int	exec_command(t_command *comm, t_list *envs, int in_pipe[2], int out_pipe[2])
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		abort_perror("Forking for program");
	if (child_pid == 0)
	{
		setup_pipe_read(comm, in_pipe);
		setup_pipe_write(comm, out_pipe);
		do_exec_call(comm, envs);
	}
	return (child_pid);
}

int	execute_all_commands(t_list *commands, t_list *envs)
{
	int	out_pipe[2];
	int	in_pipe[2];
	int	child_pid;
	int	status;

	pipe(in_pipe);
	execute_first_command(commands->content, envs, in_pipe);
	commands = commands->next;
	while (commands && commands->next)
	{
		pipe(out_pipe);
		exec_command(commands->content, envs, in_pipe, out_pipe);
		close_pipe(in_pipe);
		in_pipe[0] = out_pipe[0];
		in_pipe[1] = out_pipe[1];
		commands = commands->next;
	}
	child_pid = execute_last_command(commands->content, envs, in_pipe);
	close_pipe(in_pipe);
	status = handle_wait_pid(child_pid);
	return (status);
}

int	execute(t_list *commands, t_list *envs)
{
	int	result;

	create_heredocs(commands);
	if (ft_lstsize(commands) == 1)
		result = execute_single_command(commands->content, envs);
	else
		result = execute_all_commands(commands, envs);
	//DEBUG("after all wait\n");
	//DEBUG("\nhay %i hijos\n", ft_lstsize(commands));
	delete_heredocs();
	return (result);
}
