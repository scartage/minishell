/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/10/24 18:01:50 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "minishell.h"
#include "../errors/errors.h"

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
int ft_echo(t_list *arguments, t_list *envs)
{
	(void)envs;
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
int	ft_pwd(t_list *arguments, t_list *envs)
{
	char	buffer[PATH_MAX];
	int		len_args;
	t_list	*temp_args;

	(void)envs;
	len_args = ft_lstsize(arguments);
	if (len_args > 1)
	{
		temp_args = arguments->next;
		while (temp_args != NULL)
		{
			if (check_env_name((char *)temp_args->content) != 0)
			{
				show_error_arg("pwd ", temp_args->content,
					"not a valid identifier\n");
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

/*revisada y funciona como bash*/
/*falta que salga con el exit status de otro programa*/
/*falta manejar casos como '  3' '3  '
o numeros extremos grandes -18446744073709551617*/

/*que pasamos como argumento a show_error_arg cuando el arg es ("") o (" ")*/
int	ft_exit(t_list *arguments, t_list *envs)
{
	int	arg_count;
	int	ex_number;

	(void)envs;
	arg_count = ft_lstsize(arguments);
	ex_number = 0;
	if (arg_count == 1)
		exit(EXIT_SUCCESS);
	printf("exit\n");
	if (ft_isdigit_void((char *)arguments->next->content) != 0)
	{
		/*this does not work*/
		char *arg = arguments->next->content;
		if ((arg[0] == '\0') || (arg[0] == ' ' && arg[1] == '\0'))
			show_error_arg("exit ", NULL ,"numeric argument required");
		else
		{
			show_error_arg("exit ", (char *)arguments->next->content,
				"numeric argument required");
			exit(255);
		}
	}
	if (arg_count > 2)
	{
		show_error("exit ", "too many arguments");
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
int ft_cd(t_list *arguments, t_list *envs)
{
	(void)envs;
	int len_args = ft_lstsize(arguments);
	char *first_arg;

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
	if (first_arg[0] == '-')
	{
		show_error_arg("cd: ", first_arg, "invalid options");
		return (1);
	}
	if (len_args > 2)
	{
		show_error("cd", "too many arguments");
		return (1);
	}
	//printf("%s\n", first_arg);
	if (chdir(first_arg) != 0)
		show_error_arg("cd: ", first_arg, "No such file or directory");
	return (0);
}
