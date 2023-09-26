/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/09/26 21:09:28 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parsing/token_parser.h"

// extern t_shell g_shell;


char *ft_readline(void)
{
	char *prompt;
	char *line;

	prompt = "minishell: ";
	line = readline(prompt);
	if (line == NULL)
	{
		if (g_shell.is_executing == true)
		{
			printf("pepe el pepe\n");
			// TODO: needs cheching if it is executing anything
			//Cerramos el proceso que esta en ejecucion
			kill(g_shell.children_pid, SIGINT);
		}
		else
		{
			write(STDOUT_FILENO, "exit\n", 5);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
	}
	return (line);
}

/*Ojo: el exit tiene mas complejidad que simplemente
 * poner un exit en terminal (en bash has exit hola 0 y luego
 * revisa lo que devuelve el echo $?)*/
char *get_input(void)
{
	char *line;

	rl_catch_signals = 0;
	line = ft_readline();
	if (line[0] == '\0' || strcmp(line, "\n") == 0 || line[0] == 32)
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}
