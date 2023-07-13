/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:01 by scartage          #+#    #+#             */
/*   Updated: 2023/07/13 19:34:04 by scartage         ###   ########.fr       */
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

typedef struct s_shell {
	int			last_execution;
	t_list		*env_variables;		// list of t_env_var
	t_list		*parsed_words;
	int			level;
	bool		is_executing;
}	t_shell;

 t_shell	g_shell;

char *get_input(void);

//Temporal util functions
void printingBefore(t_list *temp_tokens);
void printAfter(t_list *temp_tokens);

#endif
