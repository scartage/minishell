/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:31 by fsoares-          #+#    #+#             */
/*   Updated: 2023/10/20 21:40:28 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "errors.h"
#include "libft.h"

void	free_globals(void)
{
	// TODO: Free all the global variables to avoid leaks
}

void	shell_error(char *reason)
{
	free_globals();
	terminate_with_error(reason);
}

static char	*prepend_shell(char *message, char *command)
{
	char	*temp;
	int		size;
	int		len;
	char	*to_add = "minishell: ";
	
	//FIXME: remove later
	to_add = "";

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

void	show_error(char *command, char *msm)
{
	char	*temp;

	temp = prepend_shell(msm, command);
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
