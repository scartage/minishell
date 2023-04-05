/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:31 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 18:38:07 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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

static char	*prepend_shell(char *message)
{
	char	*temp;
	int		size;
	int		comm_len;

	comm_len = 0;
	size = ft_strlen(message) + ft_strlen("minishell: ") + 1;
	temp = malloc(size);
	ft_strlcpy(temp, "minishell: ", size);
	ft_strlcat(temp, message, size);
	return (temp);
}

void	abort_perror(char *message)
{
	char	*temp;

	temp = prepend_shell(message);
	perror(temp);
	free(temp);
	free_globals();
	exit(1);
}
