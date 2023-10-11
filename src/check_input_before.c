/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_before.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:49 by scartage          #+#    #+#             */
/*   Updated: 2023/10/11 17:28:49 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "errors/errors.h"

/*Here we are going to check the input before we parsed it*/
static bool check_closed_quotes(const char *str, int len)
{
	int single_quotes = 0;
	int double_quotes = 0;
	int i;

	//checking if quoutes are closed
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
		show_errors_checker("Error: Quote not closed.\n");
		return (false);
	}
	return (true);
}


static bool	check_start_end_chars(const char *str, int len)
{
	if (ft_strrchr("|>", str[0]) || ft_strrchr("|><", str[len - 1]))
	{
		show_errors_checker("Error: Special characters misplaced\n");
		return (false);
	}
	return (true);
}

static bool	check_special_chars(const char *str, int len)
{
	if (ft_strnstr(str, "||", len) || ft_strnstr(str, "><", len))
	{
		show_errors_checker("Error: Invalid combinations of special characters.\n");
		return (false);
	}
	return (true);
}

bool	check_pre_parse_input(const char *str)
{
	int len = ft_strlen(str);

	if (!check_closed_quotes(str, len))
		return (false);
	if (!check_start_end_chars(str, len))
		return (false);
	if (!check_special_chars(str, len))
		return (false);
	else
		return (true);
}

