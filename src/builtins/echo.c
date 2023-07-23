/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/07/23 16:15:01 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "../inc/minishell.h"
#include "../errors/errors.h"

int echo(t_list *arguments)
{
    
    ft_lstiter(arguments->next, print_strings_echo);
    ft_printfln("");
    printf("\n");
    return 0;
}

int pwd(t_list *arguments)
{
    (void)arguments;
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    ft_printf("%s", buffer);
    return 0;
}

/*Falta revisar casos de exit y que funcione con sus parametros*/
int ft_exit(t_list *arguments)
{
    if (ft_lstsize(arguments) > 1)
        abort_perror("exit: too many arguments");
    /*else if (ft_lstiter(arguments->next, ft_isdigit_void))
        abort_perror("exit: numeric argument required");*/
    else{
        rl_clear_history();
        printf("\n");
        g_shell.last_execution = 0;
        exit(EXIT_SUCCESS);
    }
    return 0;
}
