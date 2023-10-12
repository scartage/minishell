/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/10/12 18:13:26 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>

#include "executor.h"
#include "../inc/minishell.h"
#include "../builtins/builtins.h"
#include "../errors/errors.h"
#include "../env_parser/env_parser.h"
#include "path_handler.h"
#include "file_handler.h"

char	**comm_to_args(t_command *comm)
{
	t_list *args = comm->arguments;
	char **res = protected_calloc(ft_lstsize(args) + 1, sizeof(char *));
	int i = 0;

	while (args)
	{
		res[i++] = args->content;
		args = args->next;
	}
	return (res);
}

char	*create_env_str(t_env_var *env) {
	// + 2 for the '=' and the \0
	int total_size = ft_strlen(env->name) + ft_strlen(env->content) + 2;
	char *res = protected_calloc(total_size, sizeof(char));
	ft_strlcpy(res, env->name, total_size);
	ft_strlcat(res, "=", total_size);
	ft_strlcat(res, env->content, total_size);
	return res;
}

char	**envs_to_array(t_list *envs)
{
	char **res = protected_calloc(ft_lstsize(envs) + 1, sizeof(char *));
	int i = 0;

	while (envs)
	{
		res[i++] = create_env_str(envs->content);
		envs = envs->next;
	}
	return (res);
}

void log_array(char **arr) {
	DEBUG("[");
	while(*arr) {
		DEBUG("'%s', ", *arr);
		arr++;
	}
	DEBUG("]\n");
}

void do_exec_call(t_command *comm, t_list *envs)
{
	char	*command_path;

	command_path = get_full_path(comm, envs);
	char ** args = comm_to_args(comm);
	char ** envp = envs_to_array(envs);
	//my_log("command path: %s\n", command_path);
	//my_log("args: "); log_array(args);
	//my_log("envs: "); log_array(envp);
	if (execve(command_path, args, envp) == -1)
		abort_perror("Problem executing command");
}

int	execute_first_command(t_command *first, t_list *envs, int in_pipe[2], int out_pipe[2])
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		abort_perror("Forking for program");
	if (child_pid == 0)
	{
		setup_first_pipes(first, in_pipe, out_pipe);
		do_exec_call(first, envs);
	}
	return (child_pid);
}

int	execute_all_commands(t_list *comms, t_list *envs)
{
	int			in_pipe[2];
	int			out_pipe[2];
	int			status;
	int			child;
	t_command	*command;

	pipe(in_pipe);
	while (comms)
	{
		command = comms->content;
		if (pipe(out_pipe) == -1)
			abort_perror("Creating pipe");
		child = exec_comm(command, in_pipe, out_pipe, envs);
		close_pipe(in_pipe);
		in_pipe[0] = out_pipe[0];
		in_pipe[1] = out_pipe[1];
		comms = comms->next;
	}
	if (waitpid(child, &status, 0) == -1)
		abort_perror("Waiting for last thread");
	close_pipe(out_pipe);
	while (wait(NULL) != -1)
		DEBUG("waiting for wait\n");
	return (status); //FIXME convert to actual exit code
}

char	*capture_input_heredoc(char *limiter)
{
	char		*line;
	t_string	*complete_input;

	complete_input = str_new();
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		str_append(complete_input, line);
		str_add_char(complete_input, '\n');
		free(line);
	}
	return (str_to_char(complete_input));
}
