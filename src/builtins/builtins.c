/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/11/03 20:04:22 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include "minishell.h"
#include "../errors/errors.h"
#include "builtins.h"
#include "../temp_utils.h"

bool	echo_is_valid_option(char *argument)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(argument);
	if (argument[0] != '-')
		return (false);
	while (i < len)
	{
		if (argument[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*revisada, se comporta como bash*/
/*pasa mpanic*/
int ft_echo(t_list *arguments)
{
	t_list *first_after_echo = arguments->next;
	bool n_opt = false;

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

/*revisada y testeada, se comporta como bash*/
int	ft_pwd(void)
{
	char	buffer[PATH_MAX];

	getcwd(buffer, PATH_MAX);
	ft_printf("%s\n", buffer);
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
	if (is_1_com)
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

/*revisado y corregido, se comporta como bash*/

/*TODO: - Revisar el output que da cuando cambia de dir
		- Cambiar el valor de PWD*/

/*TODO: como revisar cuando un dir tiene permisos*/
int	ft_cd(t_list *arguments, t_list *envs)
{
	int		len_args;
	char	*first_arg;

	(void)envs;
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
	if (ft_strlen(first_arg) == 0)
		return (0);
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
	if (chdir(first_arg) != 0)
	{
		if (errno == ENOTDIR)
			show_error_arg("cd: ", first_arg, "Not a directory", 0);
		else if (errno == EACCES)
			show_error_arg("cd: ", first_arg, "Permission denied", 0);
		else
			show_error_arg("cd: ", first_arg, "No such file or directory", 1);
		return (1);
	}
	return (0);
}
