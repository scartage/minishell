/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/04/02 18:58:10 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_perror(char *s)
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
		ft_perror("Cantidad de argumentos incorrecta\n");
	int_mode = 1;	
	rl_initialize();
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (!int_mode)
			ft_perror("No corresponde a la terminal\n");
		if (ft_get_imput() == 1)
			break;
	}
	return 0;
}
