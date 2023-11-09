/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:31:20 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 20:38:53 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "path_handler.h"
#include "../errors/errors.h"
#include "../envs/env_parser.h"

bool	check_exec_permissions(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
		{
			if (is_directory(command))
				return (false);
			return (true);
		}
		else
		{
			show_error(command, "Permission denied");
			exit(126);
		}
	}
	return (false);
}

static char	**split_path(char *path)
{
	char	**result;

	result = ft_split(path, ':');
	if (!result)
		abort_perror("malloc failed on split");
	return (result);
}

char	**get_path_components(t_list *envs)
{
	t_env_var	*current_env;
	char		**result;

	while (envs)
	{
		current_env = envs->content;
		if (ft_strncmp("PATH", current_env->name, 5) == 0)
		{
			result = split_path(current_env->content);
			return (result);
		}
		envs = envs->next;
	}
	return (NULL);
}

char	*build_path(char *command, char *path)
{
	char	*temp;
	size_t	total_size;
	size_t	len;

	len = ft_strlen(path);
	total_size = ft_strlen(command) + len + 2;
	temp = malloc(total_size);
	if (!temp)
		abort_perror("malloc failed while building path");
	ft_strlcpy(temp, path, total_size);
	ft_strlcpy(temp + len, "/", total_size);
	ft_strlcpy(temp + len + 1, command, total_size);
	return (temp);
}

char	*try_local_file(char *command)
{
	char	buffer[1000];
	char	*temp;

	getcwd(buffer, 1000);
	temp = build_path(command, buffer);
	if (check_exec_permissions(temp))
	{
		return (temp);
	}
	free(temp);
	return (NULL);
}
