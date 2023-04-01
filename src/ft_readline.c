/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/04/01 20:27:57 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//tenemos que hacer un strcmp
//return 2, devolvemos algo difente a 1, porque no es un error
//pero tampoco es algo que vayamos a imprimir por pantalla


char *check_imput(void)
{
	char s[1024];
	char *ptr = NULL;
	char ptrlen = 0;

	s = readline(" ");
	if (!s)
		return (NULL);
	//la idea es revisar aqui el imput, para devolverlo
	//"limpio" al get_imput
}
int ft_get_imput(void)
{
	char *line;

	rl_initialize();
	line = readline(" "); //check_imput();
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
	printf("%s\n", line);
	free(line);
	return (0);
}
