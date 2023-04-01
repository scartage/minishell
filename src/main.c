/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/04/01 19:10:28 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_perror(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}


int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int int_mode;

	if (ac != 1)
		ft_perror("Cantidad de argumentos incorrecta");
	int_mode = 1;
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode)
			write(STDOUT_FILENO, "~$ ", 2);
		if (ft_get_imput() == 1)
			break;
	}
	return 0;
}
