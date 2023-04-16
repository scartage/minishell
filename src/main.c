/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/04/16 17:31:00 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "libft.h"
#include "parsing/token_parser.h"
#include "env_parser/env_parser.h"
//#include "env_replacer/env_replacer.h"

extern t_shell g_shell;

void	ft_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	execute_input(char *input)
{
	t_list *tokens = parse_line(input);

	/*while para berificar tokens de la lista*/
	while (tokens->next)
	{
		printf("%s\n", tokens->content);
		if (tokens->next == NULL)
			break;
		tokens = tokens->next;
	}
	printf("%s\n", tokens->content);
	/*tokens = replace_env_vars(tokens, g_shell.env_variables); // b) step
	t_list *commands = to_commands(tokens); // d) step, returns t_list of t_commands depending on how many commands we have
	execute(commands);*/
}

void get_env(char **envp)
{
	/*Ojo: buscar como podemos recorrer esta lista
	para ver el nombre y contenido de las variables de entorno*/
	g_shell.env_variables = env_parser(envp);
	while (g_shell.env_variables->next)
	{
		printf("s\n", g_shell.env_variables->content->name);
		g_shell.env_variables = g_shell.env_variables->next;
	}
	printf("s\n", g_shell.env_variables->content.name);
	/*TODO: este WHILE no funciona (o no lo se usar bien)*/
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int		int_mode;
	char	*input;

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
