/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/11/03 19:39:48 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "libft.h"
#include "parsing/token_parser.h"
#include "parsing/commands.h"
#include "envs/env_parser.h"
#include "envs/env_replacer.h"
#include "errors/errors.h"
#include "signals/signals.h"
#include "executor/executor.h"
#include "temp_utils.h"

static int	execute_input(char *input, t_shell *shell, int last_status)
{
	t_list *tokens = parse_line(input);
	if (tokens == NULL)
		return (258);
	//t_list *temp_tokens = tokens;

	// printingBefore(temp_tokens);
	tokens = replacing_envars(tokens, shell->env_variables, last_status);
	// printAfter(temp_tokens);

	t_list *commands = token_to_command(tokens); // d) step, returns t_list of t_commands depending on how many commands we have
	ft_lstclear(&tokens, free);
	//ft_lstiter(commands, print_command);

	set_signal_handler(signal_handler_executing);
	last_status = execute(commands, shell->env_variables, last_status);
	set_signal_handler(signal_handler_input);
	ft_lstclear((void *)&commands, (t_del_fn)free_command);
	return (last_status);
}

/*this fn returns t_list intead of void*/
void	get_env(char **envp, t_shell *shell)
{
	shell->env_variables = env_parser(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		exit_status;
	char	*input;

	(void)av;
	set_signal_handler(signal_handler_input);
	if (ac != 1)
		ft_error("Cantidad de argumentos incorrecta\n");
	exit_status = 0;
	get_env(envp, &shell);
	rl_initialize();
	while (true)
	{
		input = get_input(exit_status);
		if (input == NULL)
			continue ;
		if (!check_pre_parse_input(input))
			continue ;
		exit_status = execute_input(input, &shell, exit_status);
	}
	return (0);
}
