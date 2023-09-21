/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/09/21 20:45:31 by scartage         ###   ########.fr       */
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
		// Configura el buffer interno de readline para que contenga "exit"
		rl_replace_line("exit", 0);
		// Muestra el contenido del buffer
		rl_redisplay();
		// Escribe un salto de línea para mover el cursor a la siguiente línea
		write(STDOUT_FILENO, "\n", 1);
		rl_clear_history();
		exit(EXIT_SUCCESS);
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
