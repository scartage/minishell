/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:53:35 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 19:44:59 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "../inc/minishell.h"

/*revisada, funciona como bash*/
int	ft_env(t_list *arguments, t_list *envs)
{
	t_list		*temp_tokens;
	t_env_var	*env_var;

	temp_tokens = envs;
	if (ft_lstsize(arguments) > 1)
	{
		show_error_arg("env", arguments->next->content,
			"no options or arguments are required", 1);
		return (1);
	}
	while (temp_tokens != NULL)
	{
		env_var = temp_tokens->content;
		if (var_exists_in_envs(env_var->name, envs) == 2)
			printf("%s=%s\n", env_var->name, env_var->content);
		if (temp_tokens->next == NULL)
			break ;
		temp_tokens = temp_tokens->next;
	}
	return (0);
}

void	show_env_vars_export(t_list *envs)
{
	t_list		*temp_tokens;
	t_env_var	*env_var;

	temp_tokens = envs;
	while (temp_tokens != NULL)
	{
		env_var = temp_tokens->content;
		if (var_exists_in_envs(env_var->name, envs) == 1)
			printf("declare -x %s\n", env_var->name);
		if (var_exists_in_envs(env_var->name, envs) == 2)
			printf("declare -x %s=\"%s\"\n", env_var->name, env_var->content);
		if (temp_tokens->next == NULL)
			break ;
		temp_tokens = temp_tokens->next;
	}
}

/*revisada funciona como bash*/
/*pasa todos los casos de mpanic*/
int	ft_export(t_list *arguments, t_list *envs)
{
	int		count_arg;
	t_list	*temp_args;
	int		exit_status;

	count_arg = ft_lstsize(arguments);
	temp_args = arguments->next;
	if (count_arg < 2)
	{
		order_envs_list(envs);
		show_env_vars_export(envs);
		return (0);
	}
	while (temp_args != NULL)
	{
		if (check_env_arg((char *)temp_args->content, envs) != 0)
		{
			show_error_arg("export: ", temp_args->content,
				"not a valid identifier", 0);
			exit_status = 1;
			//return (1);
		}
		if (temp_args->next == NULL)
			break ;
		temp_args = temp_args->next;
	}
	if (exit_status == 1)
		return (1);
	return (0);
}

/*revisada y funciona como bash*/
int	ft_unset(t_list *arguments, t_list *envs)
{
	int		count_arg;
	t_list	*temp_args;
	int exit_status;
	count_arg = ft_lstsize(arguments);
	temp_args = arguments->next;
	if (count_arg == 1)
		return (0);
	while (temp_args != NULL)
	{
		if (check_if_valid((char *)temp_args->content, &envs) != 0)
		{
			show_error_arg("unset: ", temp_args->content,
				"not a valid identifier", 0);
			exit_status = 1;
		}
		if (temp_args->next == NULL)
			break ;
		temp_args = temp_args->next;
	}
	if (exit_status == 1)
		return (1);
	return (0);
}

bool	is_builtin(t_command *command)
{
	char	*name;

	if (!command->arguments)
		return (false);
	name = command->arguments->content;
	if (ft_strncmp("echo", name, 5) == 0)
		return (true);
	if (ft_strncmp("pwd", name, 4) == 0)
		return (true);
	if (ft_strncmp("exit", name, 5) == 0)
		return (true);
	if (ft_strncmp("cd", name, 3) == 0)
		return (true);
	if (ft_strncmp("env", name, 4) == 0)
		return (true);
	if (ft_strncmp("export", name, 7) == 0)
		return (true);
	if (ft_strncmp("unset", name, 6) == 0)
		return (true);
	return (false);
}

bool	is_special_builtin(t_command *command)
{
	char	*name;

	if (!command->arguments)
		return (false);
	name = command->arguments->content;
	if (ft_strncmp("exit", name, 5) == 0)
		return (true);
	if (ft_strncmp("cd", name, 3) == 0)
		return (true);
	if (ft_strncmp("env", name, 4) == 0)
		return (true);
	if (ft_strncmp("export", name, 7) == 0)
		return (true);
	if (ft_strncmp("unset", name, 6) == 0)
		return (true);
	return (false);
}


int	call_builtin(t_list *args, t_list *envs, int last_status, bool is_1_com)
{
	char	*name;

	name = args->content;
	if (ft_strncmp("echo", name, 5) == 0)
		return (ft_echo(args));
	if (ft_strncmp("pwd", name, 4) == 0)
		return (ft_pwd());
	if (ft_strncmp("exit", name, 5) == 0)
		return (ft_exit(args, last_status, is_1_com));
	if (ft_strncmp("cd", name, 3) == 0)
		return (ft_cd(args, envs));
	if (ft_strncmp("env", name, 4) == 0)
		return (ft_env(args, envs));
	if (ft_strncmp("export", name, 7) == 0)
		return (ft_export(args, envs));
	if (ft_strncmp("unset", name, 6) == 0)
		return (ft_unset(args, envs));
	ft_putstr_fd("This should never happen, check call_builtin", 2);
	return (-1);
}
