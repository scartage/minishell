/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scartage <scartage@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:52:32 by scartage          #+#    #+#             */
/*   Updated: 2023/11/04 18:52:43 by scartage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_UTILS_H
# define TEMP_UTILS_H

# include "libft.h"
# include "../inc/minishell.h"

void	printingBefore(t_list *temp_tokens);
void	printAfter(t_list *temp_tokens);
void	print_infile(void *content2);
void	print_outfile(void *content2);
void	print_strings(void *str);
void	print_strings_echo(void *str);
int		ft_isdigit_void(void *str);
void	print_command(void *command2);
char	*fn_quote_arg(const char *arg);
char	*ft_strtrim_spaces(char *str);
#endif
