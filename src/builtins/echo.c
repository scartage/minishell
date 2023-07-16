/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:55:09 by scartage          #+#    #+#             */
/*   Updated: 2023/07/16 16:49:04 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../temp_utils.h"
#include <unistd.h>
#include <limits.h>

int echo(t_list *arguments)
{
    ft_lstiter(arguments->next, print_strings);
    ft_printfln("");
    return 0;
}

int pwd(t_list *arguments)
{
    (void)arguments;
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    ft_printf("%s", buffer);
    return 0;
}
