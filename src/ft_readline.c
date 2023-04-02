/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/04/02 19:01:58 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_readline(void)
{
	char	*prompt;

	prompt = "minishell: ";
	return (readline(prompt));
}

/*Ojo: el exit tiene mas complejidad que simplemente
 * poner un exit en terminal (en bash has exit hola 0 y luego
 * revisa lo que devuelve el echo $?)*/
int ft_get_imput(void)
{
	char *line;

	line = ft_readline();
	if (!line)
		exit(EXIT_FAILURE);
	if (line[0] == '\0' || strcmp(line, "\n") == 0)
	{	
		free(line);
		return (2);
	}
	add_history(line);
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		rl_clear_history();
		write(STDOUT_FILENO, "exit\n", 5);
		return (1);
	}
	//aqui se deberi pasar al parseo del imput,
	//supongo que sera una funcion que guarde la info en una
	//variable la cual se encuentre en una estructura
	printf("%s\n", line);
	free(line);
	return (0);
}
