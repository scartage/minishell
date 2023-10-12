/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:53:35 by scartage          #+#    #+#             */
/*   Updated: 2023/10/12 18:36:59 by scartage         ###   ########.fr       */
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
#include "../env_parser/env_parser.h"

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
