/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/10/11 21:27:40 by scartage         ###   ########.fr       */
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
#include "../signals/signals.h"

extern t_gShell g_shell;

typedef struct s_builtins_fn
{
	char *name;
	int (*fn)(t_list *);
} t_builtins_fn;

#include <stdarg.h>
void my_log(const char * format, ...)
{
  va_list args;
  va_start (args, format);
  vfprintf (stderr, format, args);
  va_end (args);
  fflush(stderr);
}

t_builtins_fn get_builtin(t_command *command)
{
	t_builtins_fn builtins[7];

	builtins[0] = (t_builtins_fn){.name = "echo", .fn = echo};
	builtins[1] = (t_builtins_fn){.name = "pwd", .fn = pwd};
	builtins[2] = (t_builtins_fn){.name = "exit", .fn = ft_exit};

	int i = 0;
	while (i < 3)
	{
		if (ft_strncmp(command->arguments->content, builtins[i].name, 20) == 0)
		{
			return builtins[i];
		}
		i++;
	}

	return (t_builtins_fn){.name = NULL, .fn = NULL};
}

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
	
	while(envs) {
		res[i++] = create_env_str(envs->content);
		envs = envs->next;
	}
	return (res);
}

void log_array(char **arr) {
	my_log("[");
	while(*arr) {
		my_log("'%s', ", *arr);
		arr++;
	}
	my_log("]\n");
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
	DEBUG("executing %s\n", command_path);
	if (execve(command_path, args, envp) == -1)
		abort_perror("Problem executing command");
}

int exec_comm(t_command *com, int in_pipe[2], int out_pipe[2], t_list *envs)
{
	int child_pid;

	child_pid = fork();
	if (child_pid == -1)
		abort_perror("Forking for program");
	if (child_pid == 0)
	{
		setup_pipes(com, in_pipe, out_pipe);
		do_exec_call(com, envs);
	}
	else
	{
		g_shell.is_executing = true;
		if (g_shell.current_child < MAX_CHILDREN)
			g_shell.children_pid[g_shell.current_child++] = child_pid;
	}
	return (child_pid);
}

void print_child_pids() {
    for (int i = 0; i < g_shell.current_child; i++) {
        DEBUG("Child PID %d: %d\n", i, g_shell.children_pid[i]);
    }
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
	print_child_pids();
}
void	execute_all_commands(t_list *comms, t_list *envs)
{
	int		in_pipe[2];
	int		out_pipe[2];
	int		status;
	int		child;
	t_command	*command;

	if (pipe(in_pipe) == -1)
		abort_perror("Creating pipe");
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
	DEBUG("after wait\n");
	// FIXME: do this correctly
	DEBUG("after print\n")
	close_pipe(out_pipe);
	while (wait(NULL) != -1) {
		DEBUG("waiting for wait\n");
	}
	clean_array_pid();
	DEBUG("after all wait\n")
	DEBUG("\nhay %i hijos\n", g_shell.current_child);
	print_child_pids();
}

void execute(t_list * commands, t_list *envs)
{
	// TODO: later handle heredocs

	t_command *command = commands->content;
	t_builtins_fn builtin = get_builtin(command);
	int result = 0;

	// fork to execute commads
	if (builtin.name != NULL)
	{
		if (ft_lstsize(command->output_files) > 0)
		{
			int bla = open("teste", O_CREAT | O_WRONLY, 0644);
			dup2(bla, STDOUT_FILENO);
			result = builtin.fn(command->arguments);
			close(bla);
		}
		result = builtin.fn(command->arguments);
	}
	else
	{
		execute_all_commands(commands, envs);
	}

	g_shell.last_execution = result;
	g_shell.is_executing = false;
}
