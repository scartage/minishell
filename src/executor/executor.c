/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/10/20 18:59:31 by fsoares-         ###   ########.fr       */
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


void print_child_pids() {
    for (int i = 0; i < g_shell.current_child; i++) {
        DEBUG("Child PID %d: %d\n", i, g_shell.children_pid[i]);
    }
}

void add_child_pid(int pid)
{
	g_shell.is_executing = true;
	if (g_shell.current_child < MAX_CHILDREN)
		g_shell.children_pid[g_shell.current_child++] = pid;
}

void clean_array_pid(void)
{
	int i;

	i = 0;
	while (i < g_shell.current_child)
	{
		g_shell.children_pid[i] = 0;
		i++;
	}
	g_shell.children_pid[i] = 0;
	g_shell.current_child = 0;
	g_shell.is_executing = false;
}

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

int	execute_single_command(t_command *command, t_list *envs)
{
	t_builtin	builtin;
	int			child_pid;
	int			result;

	result = 0;
	builtin = get_builtin(command);
	if (builtin.name != NULL)
	{
		int saved_stdin = dup(0);
		int saved_stdout = dup(1);
		setup_first_read_fd(command);
		setup_last_write_fd(command);
		result = builtin.fn(command->arguments, envs);
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
		waitpid(child_pid, &result, 0);
		result = WEXITSTATUS(result);
		add_child_pid(child_pid);
	}
	return (result);
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
	add_child_pid(child_pid);
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
	add_child_pid(child_pid);
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
	add_child_pid(child_pid);
	return (child_pid);
}

int	execute_all_commands(t_list *commands, t_list *envs)
{
	int	out_pipe[2];
	int	in_pipe[2];
	int	child;
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
	child = execute_last_command(commands->content, envs, in_pipe);
	close_pipe(in_pipe);
	waitpid(child, &status, 0);
	status = WEXITSTATUS(status);
	while (wait(NULL) != -1)
		;
	return (status);
}

void	execute(t_list *commands, t_list *envs)
{
	int	result;

	create_heredocs(commands);
	if (ft_lstsize(commands) == 1)
		result = execute_single_command(commands->content, envs);
	else
		result = execute_all_commands(commands, envs);
	DEBUG("after all wait\n");
	DEBUG("\nhay %i hijos\n", g_shell.current_child);
	print_child_pids();
	clean_array_pid();
	g_shell.last_execution = result;
	delete_heredocs();
}
