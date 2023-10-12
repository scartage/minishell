/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:20:13 by scartage          #+#    #+#             */
/*   Updated: 2023/10/12 17:30:08 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../temp_utils.h"
#include "../../inc/minishell.h"
#include <stdio.h>

void add_input_to_command(t_command * command, char * type, char * value)
{
	t_in_file	*input;

	input = protected_malloc(sizeof(t_in_file));
	if (ft_strncmp(type, "<<", 3) == 0)
	{
		input->type = HEREDOC;
		input->end_str = ft_strdup(value);
	}
	else
	{
		input->type = NORMAL;
		input->name = ft_strdup(value);
	}
	ft_lstadd_back(&command->input_files, ft_lstnew(input));
}

void add_output_to_command(t_command * command, char * type, char * value)
{
	t_out_file * output = protected_malloc(sizeof(t_out_file));
	
	output->type = WRITE;
	if (ft_strncmp(type, ">>", 3) == 0) {
		output->type = APPEND;
	}
	output->name = ft_strdup(value);
	ft_lstadd_back(&command->output_files, ft_lstnew(output));
}

void add_argument_to_command(t_command * command, char * value) {
	ft_lstadd_back(&command->arguments, ft_lstnew(ft_strdup(value)));
}

t_list /*<t_command>*/ * token_to_command(t_list * tokens)
{
	t_list * commands = NULL;
	t_command * command_list = protected_malloc(sizeof(t_command));
	char first_char;

	while (tokens != NULL)
	{
		first_char = ((char *)tokens->content)[0];
		if (first_char == '|') {
			ft_lstadd_back(&commands, ft_lstnew(command_list));
			command_list =  protected_malloc(sizeof(t_command));
		} else if (first_char == '<') {
			add_input_to_command(command_list, tokens->content, tokens->next->content);
			tokens = tokens->next;
		} else if (first_char == '>') {
			add_output_to_command(command_list, tokens->content, tokens->next->content);
			tokens = tokens->next;
		} else {
			add_argument_to_command(command_list, tokens->content);
		}
		tokens = tokens->next;
	}
	ft_lstadd_back(&commands, ft_lstnew(command_list));
	return (commands);
}
