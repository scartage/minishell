/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:53:35 by scartage          #+#    #+#             */
/*   Updated: 2023/10/25 20:42:05 by scartage         ###   ########.fr       */
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
		show_error("env", "no options or arguments are required");
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
				"not a valid identifier");
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
				"not a valid identifier");
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

t_builtin	get_builtin(t_command *command)
{
	t_builtin	builtins[7];
	int			i;

	builtins[0] = (t_builtin){.name = "echo", .fn = ft_echo};
	builtins[1] = (t_builtin){.name = "pwd", .fn = ft_pwd};
	builtins[2] = (t_builtin){.name = "exit", .fn = ft_exit};
	builtins[3] = (t_builtin){.name = "cd", .fn = ft_cd};
	builtins[4] = (t_builtin){.name = "env", .fn = ft_env};
	builtins[5] = (t_builtin){.name = "export", .fn = ft_export};
	builtins[6] = (t_builtin){.name = "unset", .fn = ft_unset};
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(command->arguments->content, builtins[i].name, 20) == 0)
		{
			return (builtins[i]);
		}
		i++;
	}
	return ((t_builtin){.name = NULL, .fn = NULL});
}
