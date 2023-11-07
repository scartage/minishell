/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:31 by fsoares-          #+#    #+#             */
/*   Updated: 2023/11/07 20:40:45 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "errors.h"
#include "libft.h"

static char	*prepend_shell(char *command, char *message)
{
	char	*temp;
	int		size;
	int		len;
	char	*to_add;

	to_add = "minishell: ";
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

void	show_error_arg(char *command, char *arg, char *msm, int opt)
{
	char	*temp;
	char	*prev;
	char	*quoted_arg;

	if (arg == NULL)
		temp = prepend_shell(command, msm);
	if (opt == 0)
	{
		quoted_arg = fn_quote_arg(arg);
		prev = ft_strjoin(command, quoted_arg);
		free(quoted_arg);
		temp = prepend_shell(prev, msm);
		free(prev);
	}
	else
	{
		prev = ft_strjoin(command, arg);
		temp = prepend_shell(prev, msm);
		free(prev);
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

	temp = prepend_shell(NULL, message);
	perror(temp);
	free(temp);
	free_globals();
	exit(1);
}
