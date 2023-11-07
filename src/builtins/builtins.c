/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:12:50 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 20:30:52 by scartage         ###   ########.fr       */
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