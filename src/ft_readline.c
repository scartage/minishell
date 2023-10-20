/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/10/20 22:22:22 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parsing/token_parser.h"


char *ft_readline(int exit_status)
{
	char *prompt;
	char *line;

	prompt = "minishell: ";
	line = readline(prompt);
	if (line == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		rl_clear_history();
		exit(exit_status);
	}
	return (line);
}

/* rl_catch_signals = 0; es una variable global de readline
 * la cual cuando esta en 0 es para que readline no use sus
 * propios manejadores de senales y podamos usar los nuestros*/
char *get_input(int exit_status)
{
	char *line;

	rl_catch_signals = 0;
	line = ft_readline(exit_status);
	if (line[0] == '\0' || strcmp(line, "\n") == 0 || line[0] == 32)
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}
