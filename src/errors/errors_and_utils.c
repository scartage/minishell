/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:31:24 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 20:29:54 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*for quoting args in error msm*/
char	*fn_quote_arg(const char *arg)
{
	int		len;
	char	*quoted_arg;

	quoted_arg = malloc(ft_strlen(arg) + 3);
	if (!quoted_arg)
	{
		abort_perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	quoted_arg[0] = '`';
	ft_strlcpy(quoted_arg + 1, arg, ft_strlen(arg) + 1);
	len = ft_strlen(quoted_arg);
	quoted_arg[len] = '\'';
	quoted_arg[len + 1] = '\0';
	return (quoted_arg);
}

void	shell_error(char *reason)
{
	terminate_with_error(reason);
}

/*This one is used in the main*/
void	ft_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}
