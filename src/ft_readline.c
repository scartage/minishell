/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:46:39 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 18:48:36 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "parsing/token_parser.h"

char	*ft_readline(int exit_status)
{
	char	*prompt;
	char	*line;

	prompt = "minishell: ";
	line = readline(prompt);
	if (line == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		rl_clear_history();
		exit(exit_status);
	}
	return (line);
}

/* rl_catch_signals = 0; we set this readline variable to 0, bc
we want to use our own signal handler*/
char	*get_input(int exit_status)
{
	char	*line;

	rl_catch_signals = 0;
	line = ft_readline(exit_status);
	if (line[0] == '\0' || strcmp(line, "\n") == 0 || line[0] == 32)
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}
