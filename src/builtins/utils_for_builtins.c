/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:32:17 by scartage          #+#    #+#             */
/*   Updated: 2023/11/01 19:11:59 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>		// para erno
#include <limits.h>

/*Puede que esta solucion no sea correcta, pero ya nos detecta numeros
mas grandes que un int los cuales no son validos*/

/*TO CHECK*/
// static int	is_valid_number(char *str)
// {
// 	char	*endptr;
// 	long	num;

// 	errno = 0;
// 	num = strtol(str, &endptr, 10);
// 	if (errno == ERANGE || *endptr != '\0' || str == endptr)
// 		return (0);
// 	return (1);
// }

// static int	check_all_numbers(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (!ft_isdigit(str[i]))
// 		{
// 			free(str);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	ft_isdigit_void(char *str)
{
	int	i;

	i = 0;
	str = ft_strtrim(str, " "); //FIXME remove leak
	if (str[i] == '-' || str[i] == '+')
		i++;
	// if (check_all_numbers(str) == 1)
	// {
	// 	free(str);
	// 	return (1);
	// }
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			free(str);
			return (1);
		}
		i++;
	}
	if (i == 0 || !ft_isdigit(str[i - 1]))
	{
		free(str);
		return (1);
	}
	// if (ft_strlen(str) >= 18)
	// {
	// 	printf("entra a revisar\n");
	// 	i = is_valid_number(str);
	// 	if (i == 1)
	// 	{
	// 		free(str);
	// 		return (1);
	// 	}
	// }
	free(str);
	return (0);
}