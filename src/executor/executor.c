/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:46:30 by scartage          #+#    #+#             */
/*   Updated: 2023/07/23 16:20:35 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../inc/minishell.h"
#include "../builtins/builtins.h"
#include <fcntl.h>

extern t_shell g_shell;

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

void execute(t_list * commands)
{
    // TODO: later handle heredocs 

    t_command * command = commands->content;
    t_builtins_fn builtin = get_builtin(command);
    int result;

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
        printf("executing command: %s\n", command->arguments->content);
        if (ft_strncmp("sleep", command->arguments->content, 6) == 0) {
            execute_sleep(command->arguments->next->content);
        }
        result = 0;
    }

    g_shell.last_execution = result;
    g_shell.is_executing = false;
}