/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:01 by scartage          #+#    #+#             */
/*   Updated: 2023/04/05 18:09:40 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>		//para el write, isatty
#include <stdlib.h>		//para el exit
#include <string.h>		//para el strcmp (temporal)
#include <stdbool.h>	//para bool
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"		//para el t_list

typedef struct s_shell {
	int			last_execution;
	t_list	*env_variables; // list of t_env_var
	t_list		*parsed_words;
	int			level;
	bool		is_executing;
}	t_shell;

 t_shell	g_shell;

//get imput
char *get_input(void);


#endif
