/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/03/28 20:48:28 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>  //para el write, isatty
#include <stdlib.h> //para el exit
#include <string.h>	//para el strcmp (temporal)

#include <readline/readline.h>
#include <readline/history.h>
int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	int int_mode;
	char *line;

	int_mode = 1;
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode)
			write(STDOUT_FILENO, "~$ ", 2);
		line = readline(" ");
		if (!line)
			exit(EXIT_SUCCESS);
		if (line[0] == '\0' || strcmp(line, "\n") == 0)
		{
			free(line);
			continue;
		}
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		printf("%s\n", line);
		free(line);
	}
	return 0;
}
