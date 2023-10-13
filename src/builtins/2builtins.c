/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:53:35 by scartage          #+#    #+#             */
/*   Updated: 2023/10/13 16:05:02 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "minishell.h"
#include "../errors/errors.h"
#include "../envs/env_parser.h"

int ft_env(t_list *arguments, t_list *envs)
{
    if (ft_lstsize(arguments) > 1)
    {
        abort_perror("env: too many arguments");
        return (1);
    }
	t_list *temp_tokens = envs;
	t_env_var *env_var;
	while (temp_tokens != NULL)
	{
		env_var = temp_tokens->content;
		printf("%s=%s\n", env_var->name, env_var->content);
		if (temp_tokens->next == NULL)
			break;
		temp_tokens = temp_tokens->next;
	}
    return 0;
}

t_builtin	get_builtin(t_command *command)
{
	t_builtin	builtins[7];
	int			i;

	builtins[0] = (t_builtin){.name = "echo", .fn = echo};
	builtins[1] = (t_builtin){.name = "pwd", .fn = pwd};
	builtins[2] = (t_builtin){.name = "exit", .fn = ft_exit};
	builtins[3] = (t_builtin){.name = "cd", .fn = ft_cd};
	builtins[4] = (t_builtin){.name = "env", .fn = ft_env};

	i = 0;
	while (i < 5)
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