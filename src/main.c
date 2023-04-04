/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/04/04 17:15:35 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "libft.h"

typedef struct s_shell {
	int		last_execution;
	t_list	*env_variables;
	int		level;
	bool	is_executing;
}	t_shell;


t_shell	g_shell;

void	ft_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int int_mode;

	if (ac != 1)
		ft_error("Cantidad de argumentos incorrecta\n");
	int_mode = 1;	
	rl_initialize();
	
	while (*envp)
	{
		printf("%s\n", *envp++);
	}
	
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (!int_mode)
			ft_error("No corresponde a la terminal\n");
		if (ft_get_imput() == 1)
			break;
	}
	return 0;
}
