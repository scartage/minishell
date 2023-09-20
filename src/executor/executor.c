/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/09/20 20:25:18 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../inc/minishell.h"
#include "../builtins/builtins.h"
#include "../errors/errors.h"
#include <fcntl.h>

extern t_gShell g_shell;

typedef struct s_builtins_fn {
    char * name;
    int (*fn)(t_list *);
}   t_builtins_fn;

t_builtins_fn get_builtin(t_command *command) {

    t_builtins_fn builtins[7];

    builtins[0] = (t_builtins_fn){.name = "echo", .fn = echo};
    builtins[1] = (t_builtins_fn){.name = "pwd", .fn = pwd};
    builtins[2] = (t_builtins_fn){.name = "exit", .fn = ft_exit};

    int i = 0;
    while (i < 3) {
        if (ft_strncmp(command->arguments->content, builtins[i].name, 20) == 0) {
            return builtins[i];
        }
        i++;
    }

    return(t_builtins_fn){.name = NULL, .fn = NULL}; 
}

void execute_sleep(char *time) {
    int child_pid = fork();
    int status;
    if (child_pid != 0)
        g_shell.children_pid = child_pid;
    if (child_pid == 0) {
        g_shell.is_executing = true;
        execl("/bin/sleep", "sleep", time, NULL);
    } else {
        wait(&status);
    }
} 

void	setup_pipes(t_command *comm, int in_pipe[2], int out_pipe[2])
{
    (void)comm;
    

    int fd = open("Makefile", O_RDONLY);
    int fd2 = open("Makefile2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    fprintf(stderr, "fd: %i, %i\n", fd, fd2);

	if (dup2(fd, STDIN_FILENO) == -1)
		abort_perror("Redirecting read end of input pipe to stdin");
	if (dup2(fd2, STDOUT_FILENO) == -1)
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

// FIXME
char *get_full_path(t_command *comm, t_list *envs) {
    (void)envs;
    return comm->arguments->content;
}

char **envs_to_array(t_list *envs) {
    (void)envs;
    char ** result = ft_calloc(2, sizeof(char *));
    char *first = ft_strdup("PATH=/usr/bin");
    result[0] = first;
    return result;
}

char **comm_to_args(t_command *comm) {
    (void)comm;
    char ** result = ft_calloc(2, sizeof(char *));
    char *first = ft_strdup("./fake_command");
    result[0] = first;
    return result;
}

void	do_exec_call(t_command *comm, t_list *envs)
{
	char	*command_path;

	command_path = get_full_path(comm, envs);
    
    execl("/bin/cat", "cat", NULL);
	// if (execve(command_path, comm_to_args(comm), envs_to_array(envs)) == -1)
	// 	abort_perror("Problem executing command");
}

void	exec_comm(t_command *com, int in_pipe[2], int out_pipe[2], t_list *envs)
{
	int		child;

	child = fork();
	if (child == -1)
		abort_perror("Forking for program");
	if (child == 0)
	{
		setup_pipes(com, in_pipe, out_pipe);
        (void)envs;
        // char myString[100];
        // read(STDIN_FILENO, myString, 99);
        // myString[99] = 0;
        // fprintf(stderr, "dgskkshksdjgs: %s\n", myString);
        // fflush(stderr);
        
		do_exec_call(com, envs);
	}
}


void    execute_all_commands(t_list *commands, t_list *envs)
{
	int		    in_pipe[2];
	int		    out_pipe[2];
	t_command   *command;

    pipe(in_pipe);
	while (commands != NULL)
	{
		command = commands->content;
		if (pipe(out_pipe) == -1)
			abort_perror("Creating pipe");
		exec_comm(command, in_pipe, out_pipe, envs);
		close_pipe(in_pipe);
		in_pipe[0] = out_pipe[0];
		in_pipe[1] = out_pipe[1];

        commands = commands->next;
	}
}

void execute(t_list * commands, t_list * envs)
{
    // TODO: later handle heredocs 

    t_command * command = commands->content;
    t_builtins_fn builtin = get_builtin(command);
    int result = 0;

    // fork to execute commads
    if (builtin.name != NULL) {
        if (ft_lstsize(command->output_files) > 0)
        {
            int bla = open("teste", O_CREAT | O_WRONLY, 0644);
            dup2(bla, STDOUT_FILENO);
            result = builtin.fn(command->arguments);
            close(bla);
        }  
        result = builtin.fn(command->arguments);
    } else {
        printf("here??\n");
        (void)envs;
        execute_all_commands(commands, envs);
    }

    g_shell.last_execution = result;
    g_shell.is_executing = false;
}
