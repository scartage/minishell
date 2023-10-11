/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_before.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:49 by scartage          #+#    #+#             */
/*   Updated: 2023/10/11 13:41:07 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/*Here we are going to check the input before we parsed it*/

bool check_pre_parse_input(const char *str)
{
	int single_quotes = 0;
	int double_quotes = 0;
	int len = ft_strlen(str);
	int i;

	//checking quoutes
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == '\"')
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
	{
		printf("Error: comilla no cerrada\n");
		return (false);
	}

	// caracteres especiales al principio o al final
	if (strchr("|>", str[0] || strchr("|><", str[len - 1])))
	{
		printf("Error: Caracteres especiales mal colocados\n");
		return (false);
	}

	//combinacion caracteres especiales
	if (strstr(str, "||") || strstr(str, "><"))
	{
		printf("Error: combinaciones no validad\n");
		return (false);
	}
    return true;
}

