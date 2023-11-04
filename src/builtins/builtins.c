/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 18:27:49 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "minishell.h"
#include "../errors/errors.h"
#include "builtins.h"
#include "../temp_utils.h"

/*revisada, se comporta como bash*/
/*pasa mpanic*/
int	ft_echo(t_list *arguments)
{
	t_list	*first_after_echo;
	bool	n_opt;

	first_after_echo = arguments->next;
	n_opt = false;
	while (first_after_echo && echo_is_valid_option(first_after_echo->content))
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

/*revisada y funciona como bash*/
/*we have to check this case
exit | ./minishell
	minishell: exit */

/*tememos que solucionar casos de numeros muy grandes

esto lo podemos gestionar con un ft_lltoa y ft_atoll*/
int	ft_exit(t_list *arguments, int last_status, bool is_1_com)
{
	int	arg_count;
	int	ex_number;

	arg_count = ft_lstsize(arguments);
	ex_number = 0;
	if (is_1_com && !IS_TEST)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (arg_count == 1)
		exit(last_status);
	if (ft_isdigit_void((char *)arguments->next->content) != 0)
	{
		show_error_arg("exit: ", (char *)arguments->next->content,
			"numeric argument required", 1);
		exit(255);
	}
	if (arg_count > 2)
	{
		show_error("exit: ", "too many arguments");
		return (1);
	}
	ex_number = ft_atoi(arguments->next->content);
	rl_clear_history();
	exit(ex_number);
	return (0);
}

static int	check_cd_arg(char *first_arg, int len_args)
{
	if (ft_strlen(first_arg) == 256)
	{
		show_error_arg("cd: ", first_arg, "File name too long", 1);
		return (1);
	}
	if (first_arg[0] == '-')
	{
		show_error_arg("cd: ", first_arg, "invalid options", 1);
		return (1);
	}
	if (len_args > 2)
	{
		show_error("cd: ", "too many arguments");
		return (1);
	}
	return (0);
}

static int	change_dir(char *first_arg, t_list *envs)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	if (ft_strlen(first_arg) == 0)
		return (0);
	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(first_arg) != 0)
	{
		if (errno == ENOTDIR)
			show_error_arg("cd: ", first_arg, "Not a directory", 1);
		else if (errno == EACCES)
			show_error_arg("cd: ", first_arg, "Permission denied", 1);
		else
			show_error_arg("cd: ", first_arg, "No such file or directory", 1);
		return (1);
	}
	update_env_content("OLDPWD", oldpwd, envs);
	getcwd(newpwd, sizeof(newpwd));
	update_env_content("PWD", newpwd, envs);
	return (0);
}

/*revisado y corregido, se comporta como bash*/
int	ft_cd(t_list *arguments, t_list *envs)
{
	int		len_args;
	char	*first_arg;

	len_args = ft_lstsize(arguments);
	errno = 0;
	if (len_args == 1)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			show_error("cd", "something went wrong");
			return (1);
		}
		return (0);
	}
	first_arg = (char *)arguments->next->content;
	if (check_cd_arg(first_arg, len_args) != 0)
		return (1);
	if (change_dir(first_arg, envs) != 0)
		return (1);
	return (0);
}
