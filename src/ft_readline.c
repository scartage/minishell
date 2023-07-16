/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/07/16 14:30:59 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parsing/token_parser.h"

//extern t_shell g_shell;

char	*ft_readline(void)
{
	char	*prompt;

	prompt = "minishell: ";
	return (readline(prompt));
}

/*Ojo: el exit tiene mas complejidad que simplemente
 * poner un exit en terminal (en bash has exit hola 0 y luego
 * revisa lo que devuelve el echo $?)*/
char	*get_input(void)
{
	char	*line;

	printf("inside input\n");
	line = ft_readline();
	if (!line)
		exit(EXIT_SUCCESS);
	if (line[0] == '\0' || strcmp(line, "\n") == 0 || line[0] == 32)
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		rl_clear_history();
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	return (line);
}
