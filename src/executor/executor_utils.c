/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:17:35 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/25 20:39:42 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "../envs/env_parser.h"

char	**comm_to_args(t_command *comm)
{
	t_list	*args;
	char	**res;
	int		i;

	args = comm->arguments;
	res = protected_calloc(ft_lstsize(args) + 1, sizeof(char *));
	i = 0;
	while (args)
	{
		res[i++] = args->content;
		args = args->next;
	}
	return (res);
}

char	*create_env_str(t_env_var *env)
{
	int		total_size;
	char	*res;
	char	*name;
	char	*content;

	if (env && env->name)
		name = env->name;
	else
		name = "";
	if (env && env->content)
		content = env->content;
	else
		content = "";
	total_size = ft_strlen(name) + ft_strlen(content) + 2;
	res = protected_calloc(total_size, sizeof(char));
	ft_strlcpy(res, name, total_size);
	ft_strlcat(res, "=", total_size);
	ft_strlcat(res, content, total_size);
	return (res);
}

char	**envs_to_array(t_list *envs)
{
	char	**res;
	int		i;

	res = protected_calloc(ft_lstsize(envs) + 1, sizeof(char *));
	i = 0;
	while (envs)
	{
		res[i++] = create_env_str(envs->content);
		envs = envs->next;
	}
	return (res);
}
