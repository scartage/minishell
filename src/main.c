/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/10/03 19:21:29 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "libft.h"
#include "parsing/token_parser.h"
#include "parsing/commands.h"
#include "env_parser/env_parser.h"
#include "env_replacer/env_replacer.h"
#include "errors/errors.h"
#include "signals/signals.h"
#include "executor/executor.h"
#include "temp_utils.h"

extern t_gShell g_shell;

void	execute_input(char *input, t_shell *shell)
{
	t_list *tokens = parse_line(input);
	//t_list *temp_tokens = tokens;

	//printingBefore(temp_tokens);
	tokens = replacing_envars(tokens, shell->env_variables);
	//printAfter(temp_tokens);

	t_list *commands = token_to_command(tokens); // d) step, returns t_list of t_commands depending on how many commands we have
	ft_lstiter(commands, print_command);
	execute(commands, shell->env_variables);
}
 
/*this fn returns t_list intead of void*/
void	get_env(char **envp, t_shell *shell)
{
	shell->env_variables = env_parser(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		int_mode;
	char	*input;

	(void)ac;
	(void)av;

	signals(1);
	if (ac != 1)
		ft_error("Cantidad de argumentos incorrecta\n");
	int_mode = 1;
	get_env(envp, &shell);
	rl_initialize();
	while (int_mode)
	{
		int_mode = isatty(STDIN_FILENO);
		if (!int_mode)
			ft_error("No corresponde a la terminal\n");
		g_shell.is_executing = false;
		input = get_input();
		if (input == NULL)
			continue ;
		execute_input(input, &shell);
		/*hola buenas dias*/
		/*hola buenas noches*/
	}
	return (0);
}
