/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:20:28 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 20:28:24 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "../builtins/builtins.h"
#include "../envs/env_parser.h"
#include "path_handler.h"
#include "pipe_handler.h"

char	**comm_to_args(t_command *comm);
char	**envs_to_array(t_list *envs);

void	do_exec_call(t_command *comm, t_list *envs, int last_status)
{
	char		*command_path;
	char		**args;
	char		**envp;
	int			return_code;

	if (is_builtin(comm))
	{
		return_code = call_builtin(comm->arguments, envs, last_status, false);
		exit(return_code);
	}
	else
	{
		if (!comm->arguments)
			exit(0);
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

int	execute_special_builtin(t_command *command, t_list *envs, int last_status)
{
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	setup_first_read_fd(command);
	setup_last_write_fd(command);
	status = call_builtin(command->arguments, envs, last_status, true);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (status);
}

int	execute_single_command(t_command *command, t_list *envs, int last_status)
{
	int	child_pid;
	int	status;

	if (is_special_builtin(command))
		status = execute_special_builtin(command, envs, last_status);
	else
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			setup_first_read_fd(command);
			setup_last_write_fd(command);
			do_exec_call(command, envs, last_status);
		}
		status = handle_wait_pid(child_pid);
	}
	return (status);
}
