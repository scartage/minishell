/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:20:13 by scartage          #+#    #+#             */
/*   Updated: 2023/07/16 16:03:12 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../temp_utils.h"
#include <stdio.h>

typedef enum e_in_type {
	NORMAL,  // fichero: <
	HEREDOC, // El heredoc: <<
} t_in_type;

typedef struct s_in_file {
	char *name;      // name of the file, or the string that represents the end of the input
	t_in_type type;
} t_in_file;

typedef enum e_out_type {
	WRITE,  // >
	APPEND, // >>
} t_out_type;

typedef struct s_out_file {
	char * name;
	t_out_type type;
} t_out_file;

typedef struct s_command {
	t_list * input_files;   // de t_in_file, lista de strings que contine los varios files de entrada en orden de aparecimiento
	t_list * output_files;  // de t_out_file, lista de out_files que contiene los files de salida en orden de aparecimiento
	t_list * arguments;     // de char *, array de strings que contiene los argumentos
} t_command;

void add_input_to_command(t_command * command, char * type, char * value)
{
	t_in_file * input = protected_malloc(sizeof(t_in_file));
	
	input->type = NORMAL;
	if (ft_strncmp(type, "<<", 3) == 0) {
		input->type = HEREDOC;
	}
	input->name = ft_strdup(value);
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
	printf("token to command: \n");
	t_list * commands = NULL;
	t_command * current = protected_malloc(sizeof(t_command));
	char first_char;

	while (tokens != NULL)
	{
		first_char = ((char *)tokens->content)[0];
		if (first_char == '|') {
			ft_lstadd_back(&commands, ft_lstnew(current));
			current =  protected_malloc(sizeof(t_command));
		} else if (first_char == '<') {
			add_input_to_command(current, tokens->content, tokens->next->content);
			tokens = tokens->next;
		} else if (first_char == '>') {
			add_output_to_command(current, tokens->content, tokens->next->content);
			tokens = tokens->next;
		} else {
			add_argument_to_command(current, tokens->content);
		}
		tokens = tokens->next;
	}
	ft_lstadd_back(&commands, ft_lstnew(current));
	return (commands);
}
