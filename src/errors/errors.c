/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:31 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/25 19:01:12 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "errors.h"
#include "libft.h"
#include "../temp_utils.h"

void	free_globals(void)
{
	// TODO: Free all the global variables to avoid leaks
}

void	shell_error(char *reason)
{
	free_globals();
	terminate_with_error(reason);
}

static char	*prepend_shell(char *command, char *message)
{
	char	*temp;
	int		size;
	int		len;
	char	*to_add = "minishell: ";
	
	// //FIXME: remove later
	// to_add = "";

	size = ft_strlen(message) + ft_strlen(to_add) + 1;
	if (command)
		size += ft_strlen(command) + 3;
	temp = malloc(size);
	len = ft_strlcpy(temp, to_add, size);
	if (command)
	{
		len += ft_strlcpy(temp + len, command, size - len);
		len += ft_strlcpy(temp + len, ": ", size - len);
	}
	ft_strlcpy(temp + len, message, size - len);
	return (temp);
}

void	show_error_arg(char *command, char *arg, char *msm)
{
	char	*temp;
	char	*prev;
	char	*quoted_arg;

	if (arg == NULL)
		temp = prepend_shell(command, msm);
	else
	{
		quoted_arg = fn_quote_arg(arg);
		prev = ft_strjoin(command, quoted_arg);
		free(quoted_arg);
		temp = prepend_shell(prev, msm);
	}
	write(STDERR_FILENO, temp, ft_strlen(temp));
	write(STDERR_FILENO, "\n", 1);
	free(temp);
}

void	show_error(char *command, char *msm)
{
	char	*temp;

	temp = prepend_shell(command, msm);
	write(STDERR_FILENO, temp, ft_strlen(temp));
	write(STDERR_FILENO, "\n", 1);
	free(temp);
}

void	abort_perror(char *message)
{
	char	*temp;

	temp = prepend_shell(message, NULL);
	perror(temp);
	free(temp);
	free_globals();
	exit(1);
}

/*This one is used in the main*/
void	ft_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}
