/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/10/12 17:12:22 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "../inc/minishell.h"
#include "../errors/errors.h"

int echo(t_list *arguments, t_list *envs)
{
	(void)envs;
	ft_lstiter(arguments->next, print_strings_echo);
	ft_printfln("");
	printf("\n");
	return 0;
}

int pwd(t_list *arguments, t_list *envs)
{
	(void)envs;
	(void)arguments;
	char buffer[PATH_MAX];
	getcwd(buffer, PATH_MAX);
	ft_printf("%s\n", buffer);
	return 0;
}

/*Falta revisar casos de exit y que funcione con sus parametros*/
int ft_exit(t_list *arguments, t_list *envs)
{
	(void)envs;
	int arg_count = ft_lstsize(arguments);
	int ex_number = 0;

	if (arg_count > 2)
	{
		abort_perror("exit: too many arguments");
		return (1);
	}
	if (arg_count == 2)
	{
		if (ft_isdigit_void(arguments->next->content) == 0)
		{
			abort_perror("exit: numeric argument required");
			return (1);
		}
		ex_number = ft_atoi(arguments->next->content);
	}
	printf("exit\n");
	rl_clear_history();
	g_shell.last_execution = 0;
	exit(ex_number);
	return 0;
}
