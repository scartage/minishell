/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/10/10 20:54:07 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parsing/token_parser.h"

extern t_gShell g_shell;


char *ft_readline(void)
{
	char *prompt;
	char *line;

	prompt = "minishell: ";
	line = readline(prompt);
	if (line == NULL)
	{
		if (g_shell.children_pid != 0)
		{
			printf("pid: %d\n", g_shell.children_pid);
			printf("cerrando el hijo\n");
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
 * revisa lo que devuelve el echo $?)
 * 
 * 
 * rl_catch_signals = 0; es una variable global de readline
 * la cual cuando esta en 0 es para que readline no use sus
 * propios manejadores de senales y podamos usar los nuestros*/
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
