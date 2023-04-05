/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/04/05 19:37:40 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parsing/token_parser.h"
#include "libft.h"

#include "env_parser/env_parser.h"

extern t_shell g_shell;

void	ft_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	execute_input(char *input)
{
	t_list *tokens = parse_line(input);
	if (tokens->content != NULL)
		printf("%s\n", tokens->content);
	/*tokens = replace_env_vars(tokens, g_shell.envs); // b) step
	t_list *commands = to_commands(tokens); // d) step, returns t_list of t_commands depending on how many commands we have
	execute(commands);*/
}

void get_env(char **envp)
{
	/*en la funcion que sigue, tenemos que hacer un parser, donde nos
	 * separe el nombre del contenido, todo lo que este antes del
	 * primer (=)sera el nombre, el resto es el contenido.
	 *
	 * luego de tener una lista con esto, tenemos que hacer una funcion
	 * en la cual al pasarle el nombre de una variable nos devuelva su contenido
	 * para por ultimo, tener una funcion donde nos busque "nombres de variables
	 * (tipo $(USER)) y remplace el contenido en la lista de tokens que tenmemos.*/ 
	g_shell.env_variables = env_parser(envp);
	
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int int_mode;
	char *input;

	if (ac != 1)
		ft_error("Cantidad de argumentos incorrecta\n");
	int_mode = 1;
	get_env(envp);
	rl_initialize();
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (!int_mode)
			ft_error("No corresponde a la terminal\n");
		input = get_input();
		if (input == NULL)
			break;
		execute_input(input);	
	}
	return 0;
}
