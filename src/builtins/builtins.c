/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/10/19 14:54:39 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "../inc/minishell.h"
#include "../errors/errors.h"

/*revisada, se comporta como bash*/
int ft_echo(t_list *arguments, t_list *envs)
{
	(void)envs;
	t_list *first_after_echo = arguments->next;
	bool n_opt = false;

	if (first_after_echo == NULL)
	{
		printf("\n");
		return (0);
	}
	while (strcmp(first_after_echo->content, "-n") == 0)
	{
		if (!n_opt)
			n_opt = true;
		first_after_echo = first_after_echo->next;
	}
	while (first_after_echo)
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

/*revisada y testeada, se comporta como bash*/
int ft_pwd(t_list *arguments, t_list *envs)
{
	char	buffer[PATH_MAX];
	int		len_args;

	(void)envs;
	len_args = ft_lstsize(arguments);
	if (len_args > 1)
	{
		t_list *temp_args = arguments->next;
		while (temp_args != NULL)
		{
			if (check_env_name((char *)temp_args->content) != 0)
			{
				char *prev = ft_strjoin("pwd: ", temp_args->content);
				char *full_error_msm = ft_strjoin(prev, ": not a valid identifier\n");
				show_errors_checker(full_error_msm);
				return (1);
			}
			if (temp_args->next == NULL)
				break ;
			temp_args = temp_args->next;
		}
	}
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

	if (ft_isdigit_void((char *)arguments->next->content) == 0)
	{
		char *prev = ft_strjoin("exit: ", arguments->next->content);
		char *full_error_msm = ft_strjoin(prev, ": numeric argument required");
		printf("exit\n");
		show_errors_checker(full_error_msm);
		exit(255);
	}
	if (arg_count > 2)
	{
		printf("exit\n");
		show_errors_checker("exit: too many arguments\n");
		return (1);
	}
	// if (arg_count == 2)
	// {
	// 	if (ft_isdigit_void(arguments->next->content) == 0)
	// 	{
	// 		char *prev = ft_strjoin("exit: ", arguments->next->content);
	// 		char *full_error_msm = ft_strjoin(prev, ": numeric argument required");
	// 		printf("exit\n");
	// 		show_errors_checker(full_error_msm);
	// 		exit(255);
	// 	}
	// 	ex_number = ft_atoi(arguments->next->content);
	// }
	ex_number = ft_atoi(arguments->next->content);
	printf("exit\n");
	rl_clear_history();
	g_shell.last_execution = 0;
	exit(ex_number);
	return (0);
}

/*revisado y corregido, se comporta como bash*/
int ft_cd(t_list *arguments, t_list *envs)
{
	(void)envs;
	int len_args = ft_lstsize(arguments);
	char *first_arg;

	if (len_args == 1)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			show_errors_checker("cd: something went wrong\n");
			return (1);
		}
		return (0);
	}
	first_arg = (char *)arguments->next->content;
	if (len_args > 2)
	{
		show_errors_checker("cd: too many arguments\n");
		return (1);
	}
	if (first_arg[0] == '-')
	{
		show_errors_checker("cd: invalid options\n");
		return (1);
	}
	printf("%s\n", first_arg);
	if (chdir(first_arg) != 0)
		show_errors_checker("cd: something went wrong\n");
	return (0);
}
