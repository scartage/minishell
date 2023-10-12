
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

#include "executor.h"
#include "../inc/minishell.h"
#include "../builtins/builtins.h"
#include "../errors/errors.h"
#include "path_handler.h"
#include "pipe_handler.h"

char	**comm_to_args(t_command *comm);
char	**envs_to_array(t_list *envs);
void	handle_heredocs(t_list *commands);

void	do_exec_call(t_command *comm, t_list *envs)
{
	char		*command_path;
	char		**args;
	char		**envp;
	t_builtin	builtin;

	builtin = get_builtin(comm);
	if (builtin.name != NULL)
		execute_builtin(builtin, comm, envs);
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
		result = execute_builtin(builtin, command, envs);
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
		//FIXME: update is running flags
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
	while (wait(NULL) != -1)
		;
	//FIXME: update is running flags
	return (0);
}

void	execute(t_list *commands, t_list *envs)
{
	int	result;

	handle_heredocs(commands);
	if (ft_lstsize(commands) == 1)
		result = execute_single_command(commands->content, envs);
	else
		result = execute_all_commands(commands, envs);

	g_shell.last_execution = result;
	g_shell.is_executing = false;
}
