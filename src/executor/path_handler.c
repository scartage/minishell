/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:25:03 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/13 16:05:13 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "path_handler.h"
#include "../errors/errors.h"
#include "../envs/env_parser.h"

#define DEF "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

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
	return (split_path(DEF));
}

static char	*build_path(char *command, char *path)
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

void show_error(char *message) {
	write(STDERR_FILENO, message, ft_strlen(message));
}

static bool	check_exec_permissions(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (true);
		else
		{
			show_error("Permission denied");
			exit(126);
		}
	}
	return (false);
}

static char	*search_path(char *command, t_list *envs)
{
	char	*temp;
	char	**path;
	int		i;

	i = 0;
	path = get_path_components(envs);
	while (path[i])
	{
		temp = build_path(command, path[i]);
		if (check_exec_permissions(temp))
		{
			ft_free_split(path);
			return (temp);
		}
		free(temp);
		i++;
	}
	ft_free_split(path);
	return (NULL);
}

char	*get_full_path(t_command *cmd, t_list *envs)
{
	char	*result;
	char	*command;

	command = cmd->arguments->content;
	DEBUG("command: %s\n", command);
	if (ft_strchr(command, '/') != NULL )
	{
		if (check_exec_permissions(command))
			return (command);
		show_error("minishell: No such file or directory");
		exit(127);
	}
	result = search_path(command, envs);
	if (!result)
	{
		char *prefix = "minishell: ";
		char *temp_join = ft_strjoin(prefix, command);
		char *full_error_msm = ft_strjoin(temp_join, ": command not found\n");
		show_error(full_error_msm);
		exit(127);
	}
	return (result);
}
