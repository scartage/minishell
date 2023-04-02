/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:05:17 by scartage          #+#    #+#             */
/*   Updated: 2023/04/02 18:43:19 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Aqui guardamos funciones utiles*/

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
void	ft_parse(char *input)
{
	bool double_quote;
	bool simple_quote;

	while(input[i])
	{
		if (input[i] == '"' && !simple_quote)
			double_quote = true;
	}
}

while (true)
{
	input = getline();
	if (!input)
		exit (1);
	ft_parse(input);

}*/
