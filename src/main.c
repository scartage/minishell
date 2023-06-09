/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/07/11 19:10:25 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "libft.h"
#include "parsing/token_parser.h"
#include "env_parser/env_parser.h"
#include "env_replacer/env_replacer.h"

//#include "env_replacer/env_replacer.h"

extern t_shell g_shell;

void	ft_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void printingBefore(t_list *temp_tokens)
{
	/*while para verificar tokens de la lista*/
	printf("---before env_parsing---\n");
	if (temp_tokens->content == NULL)
	{
		printf("No correct input\n");
		return ;
	}
	while (temp_tokens->content != NULL)
	{
		printf("token: [%s]\n", (char *)temp_tokens->content);
		if (temp_tokens->next == NULL)
			break;
		temp_tokens = temp_tokens->next;
	}
	printf("---Go to replace the env_vars---");
	printf("\n");
}

void printAfter(t_list *temp_tokens)
{
	printf("---after env_replacing---\n");
	while (temp_tokens->content != NULL)
	{
		printf("new token content: [%s]\n", (char *)temp_tokens->content);
		if (temp_tokens->next == NULL)
			break;
		temp_tokens = temp_tokens->next;
	}
	printf("fins ara\n");	
}


void	execute_input(char *input)
{
	t_list *tokens = parse_line(input);
	t_list *temp_tokens = tokens;

	printingBefore(temp_tokens);
	tokens = replacing_envars(tokens, g_shell.env_variables);
	printAfter(temp_tokens);

	/*t_list *commands = to_commands(tokens); // d) step, returns t_list of t_commands depending on how many commands we have
	execute(commands);*/
}

void get_env(char **envp)
{
	g_shell.env_variables = env_parser(envp);
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
		/*input = sanitize_input(input);  //trimea. i mira no esta vacio, y ademas chekea unclosed quotes
		if(!input)
			continue;*/
		if (input == NULL)
			continue;
		execute_input(input);	
	}
	return 0;
}
