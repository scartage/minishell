/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/10/13 21:06:04 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "minishell.h"
#include "../errors/errors.h"

int echo(t_list *arguments, t_list *envs)
{
	(void)envs;
	t_list *first_after_echo = arguments->next;
	bool n_opt = false;

	if (ft_strncmp(first_after_echo->content, "-n", 3) == 0)
	{
		n_opt = true;
		first_after_echo = first_after_echo->next;
	}
	while(first_after_echo)
	{
		printf("%s", (char *)first_after_echo->content);
		first_after_echo = first_after_echo->next;
		if (first_after_echo)
			printf(" ");
	}
	if (!n_opt)
		printf("\n");
	return (0);
}

int pwd(t_list *arguments, t_list *envs)
{
	(void)envs;
	int len_args = ft_lstsize(arguments);

	if (len_args > 1)
	{
		abort_perror("pwd: too many arguments");
		return (1);
	}
	char buffer[PATH_MAX];
	getcwd(buffer, PATH_MAX);
	ft_printf("%s\n", buffer);
	return (0);
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
			char *full_error_msm = ft_strjoin(arguments->next->content, ": numeric argument required");
			printf("exit\n");
			abort_perror(full_error_msm);
			exit(255);
		}
		ex_number = ft_atoi(arguments->next->content);
	}
	printf("exit\n");
	rl_clear_history();
	g_shell.last_execution = 0;
	exit(ex_number);
	return (0);
}

/*to check and test*/
int ft_cd(t_list *arguments, t_list *envs)
{
	(void)envs;
	int len_args = ft_lstsize(arguments);
	char *first_arg = (char *)arguments->next->content;
	if (len_args > 2)
	{
		abort_perror("cd: too many arguments");
		return (1);
	}
	if (first_arg[0] == '-')
	{
		abort_perror("cd: invalid option");
		return (1);
	}
	printf("%s\n", first_arg);
	if (chdir(first_arg) != 0)
		abort_perror("cd: something went wrong");
	return (0);
}
