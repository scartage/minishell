/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:01 by scartage          #+#    #+#             */
/*   Updated: 2023/07/16 16:38:18 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>				//para el write, isatty
#include <stdlib.h>				//para el exit
#include <string.h>				//para el strcmp (temporal)
#include <stdbool.h>			//para bool
#include <readline/readline.h>	//para obtener input
#include <readline/history.h>	//historial del input
#include "../libft/libft.h"		//para el t_list

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

typedef struct s_shell {
	int			last_execution;
	t_list		*env_variables;		// list of t_env_var
	t_list		*parsed_words;
	int			level;              // for shells inside shells
	bool		is_executing;
}	t_shell;

 t_shell	g_shell;

char *get_input(void);

#endif
