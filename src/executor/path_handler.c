/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:25:03 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 20:44:04 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "path_handler.h"
#include "../errors/errors.h"
#include "../envs/env_parser.h"

bool	check_exec_permissions(char *command);
char	**get_path_components(t_list *envs);
char	*build_path(char *command, char *path);
char	*try_local_file(char *command);

char	*search_path(char *command, t_list *envs)
{
	char	*temp;
	char	**path;
	int		i;

	i = 0;
	path = get_path_components(envs);
	while (path && path[i])
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
	return (try_local_file(command));
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

char	*exit_error_helper(char *comm, char *msg, int status)
{
	show_error(comm, msg);
	exit(status);
	return (NULL);
}

char	*get_full_path(t_command *cmd, t_list *envs)
{
	char	*result;
	char	*command;

	command = cmd->arguments->content;
	if (ft_strchr(command, '/') != NULL )
	{
		if (check_exec_permissions(command))
			return (command);
		if (is_directory(command))
			return (exit_error_helper(command, "is a directory", 126));
		else
			return (exit_error_helper(command,
					"No such file or directory", 127));
	}
	result = search_path(command, envs);
	if (!result)
		return (exit_error_helper(command, "command not found", 127));
	return (result);
}
