/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 20:50:50 by fsoares-         ###   ########.fr       */
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
#include "builtins/builtins.h"

static int	execute_input(char *input, t_shell *shell, int last_status)
{
	t_list	*tokens;
	t_list	*commands;

	input = replace_envs(input, shell->env_variables, last_status);
	tokens = parse_line(input);
	if (tokens == NULL)
		return (0);
	tokens = remove_quotes(tokens);
	if (!valid_token_seq(tokens))
	{
		ft_lstclear(&tokens, free_token);
		return (258);
	}
	commands = token_to_command(tokens);
	ft_lstclear(&tokens, free_token);
	set_signal_handler(signal_handler_executing);
	last_status = execute(commands, shell->env_variables, last_status);
	set_signal_handler(signal_handler_input);
	ft_lstclear((void *)&commands, (t_del_fn)free_command);
	return (last_status);
}

void	get_env(char **envp, t_shell *shell)
{
	shell->env_variables = env_parser(envp);
	remove_if_valid("OLDPWD", &shell->env_variables);
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
		exit_status = execute_input(input, &shell, exit_status);
	}
	return (0);
}
