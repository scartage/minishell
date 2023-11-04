/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:20:13 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 17:30:01 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../temp_utils.h"
#include "minishell.h"
#include <stdio.h>

void	add_input(t_command *command, t_token *type, t_token *value)
{
	t_in_file	*input;

	input = protected_malloc(sizeof(t_in_file));
	if (ft_strncmp(type->value, "<<", 3) == 0)
	{
		input->type = HEREDOC;
		input->end_str = ft_strdup(value->value);
	}
	else
	{
		input->type = NORMAL;
		input->name = ft_strdup(value->value);
	}
	ft_lstadd_back(&command->input_files, ft_lstnew(input));
}

void	add_output(t_command *command, t_token *type, t_token *value)
{
	t_out_file	*output;

	output = protected_malloc(sizeof(t_out_file));
	output->type = WRITE;
	if (ft_strncmp(type->value, ">>", 3) == 0)
	{
		output->type = APPEND;
	}
	output->name = ft_strdup(value->value);
	ft_lstadd_back(&command->output_files, ft_lstnew(output));
}

void	add_redirection(t_command *command, t_token *type, t_token *value)
{
	char	first_char;

	first_char = type->value[0];
	if (first_char == '>')
		add_output(command, type, value);
	else
		add_input(command, type, value);
}

void	add_argument_to_command(t_command *command, t_token *value)
{
	ft_lstadd_back(&command->arguments, ft_lstnew(ft_strdup(value->value)));
}

t_list	*token_to_command(t_list *tokens)
{
	t_list		*commands;
	t_command	*new_comm;
	t_token		*token;
	char		first_char;

	commands = NULL;
	new_comm = protected_malloc(sizeof(t_command));
	while (tokens != NULL)
	{
		token = tokens->content;
		first_char = token->value[0];
		if (first_char == '|' && token->type == PIPE)
		{
			ft_lstadd_back(&commands, ft_lstnew(new_comm));
			new_comm = protected_malloc(sizeof(t_command));
		}
		else if ((first_char == '<' || first_char == '>') && token->type == REDIR)
		{
			add_redirection(new_comm, tokens->content, tokens->next->content);
			tokens = tokens->next;
		}
		else
			add_argument_to_command(new_comm, tokens->content);
		tokens = tokens->next;
	}
	ft_lstadd_back(&commands, ft_lstnew(new_comm));
	return (commands);
}

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
