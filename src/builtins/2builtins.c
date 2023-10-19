/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:53:35 by scartage          #+#    #+#             */
/*   Updated: 2023/10/19 13:32:21 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "../inc/minishell.h"

int ft_env(t_list *arguments, t_list *envs)
{
	t_list *temp_tokens = envs;
	t_env_var *env_var;

    if (ft_lstsize(arguments) > 1)
    {
		show_errors_checker("env: too many arguments\n");
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

void show_env_vars_export(t_list *envs)
{
	t_list *temp_tokens = envs;
	t_env_var *env_var;
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

/*debemos revisar cuantos argumentos tenemos, de ahi, revisar que estos sean validos*/

/*si tenemos varios argumentos y uno es erroneo, ese, no lo guarda EL RESTO SI

si tenemos un env sin valor SI lo mostramos*/
int ft_export(t_list *arguments, t_list *envs)
{
    int count_arg = ft_lstsize(arguments);
	t_list *temp_args = arguments->next;

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
			char *prev = ft_strjoin("export: ", temp_args->content);
			char *full_error_msm = ft_strjoin(prev, ": not a valid identifier\n");
			show_errors_checker(full_error_msm);
		}
		if (temp_args->next == NULL)
			break ;
		temp_args = temp_args->next;
	}
    return (0);
}

int ft_unset(t_list *arguments, t_list *envs)
{
	int count_arg = ft_lstsize(arguments);
	t_list *temp_args = arguments->next;

    if (count_arg == 1)
        return (0);
	while (temp_args != NULL)
	{
		if (check_if_valid((char *)temp_args->content, &envs) != 0)
		{
			char *prev = ft_strjoin("unset: ", temp_args->content);
			char *full_error_msm = ft_strjoin(prev, ": not a valid identifier\n");
			show_errors_checker(full_error_msm);
		}
		if (temp_args->next == NULL)
			break;
		temp_args = temp_args->next;
	}
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
	builtins[6]	= (t_builtin){.name = "unset", .fn = ft_unset};

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

int	execute_builtin(t_builtin builtin, t_command *command, t_list *envs)
{
	//FIXME: handle redirections
	return (builtin.fn(command->arguments, envs));
}