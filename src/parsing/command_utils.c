/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:48:57 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/09 20:49:56 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../temp_utils.h"
#include "minishell.h"
#include "../errors/errors.h"
#include <stdio.h>

void	free_in_files(t_in_file *in_file)
{
	free(in_file->end_str);
	free(in_file->name);
	free(in_file);
}

void	free_out_files(t_out_file *out_file)
{
	free(out_file->name);
	free(out_file);
}

void	free_command(t_command *command)
{
	ft_lstclear((void *)&command->arguments, free);
	ft_lstclear((void *)&command->input_files, (t_del_fn)free_in_files);
	ft_lstclear((void *)&command->output_files, (t_del_fn)free_out_files);
	free(command);
}

void	add_argument_to_command(t_command *command, t_token *value)
{
	ft_lstadd_back(&command->arguments, ft_lstnew(ft_strdup(value->value)));
}

bool	show_syntax_error(char *val)
{
	t_string	*err;

	err = str_new();
	str_append(err, "syntax error near unexpected token `");
	str_append(err, val);
	str_append(err, "'");
	show_error(NULL, err->buffer);
	str_free(err);
	return (false);
}
