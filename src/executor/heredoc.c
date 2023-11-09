/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:23:16 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 17:55:31 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../../inc/minishell.h"

#define NAME_SIZE 200
#define TEMP_FILE ".__tmp_file_"

void	temp_file_name(char *buffer, int id)
{
	char	*id_str;

	ft_strlcpy(buffer, TEMP_FILE, NAME_SIZE);
	id_str = ft_itoa(id);
	ft_strlcat(buffer, id_str, NAME_SIZE);
	free(id_str);
}

int	create_temp_file(t_in_file *in_file, int id)
{
	int		fd;
	char	name[NAME_SIZE];

	temp_file_name(name, id);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	in_file->name = strdup(name);
	return (fd);
}

void	capture_input_heredoc(t_in_file *in_file, int id)
{
	char	*line;
	int		temp_fd;
	int		end_str_len;

	end_str_len = ft_strlen(in_file->end_str);
	temp_fd = create_temp_file(in_file, id);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(in_file->end_str,
				line, end_str_len) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, temp_fd);
		free(line);
	}
	close(temp_fd);
}

void	create_heredocs(t_list *commands)
{
	t_command	*comm;
	t_list		*in_files;
	t_in_file	*in_file;
	int			i;

	i = 0;
	while (commands)
	{
		comm = commands->content;
		in_files = comm->input_files;
		while (in_files)
		{
			in_file = in_files->content;
			if (in_file->type == HEREDOC)
				capture_input_heredoc(in_file, i);
			in_files = in_files->next;
			i++;
		}
		commands = commands->next;
	}
}

void	delete_heredocs(void)
{
	int		i;
	int		status;
	char	name[NAME_SIZE];

	i = 0;
	status = 0;
	while (status >= 0)
	{
		temp_file_name(name, i);
		status = unlink(name);
		i++;
	}
}
