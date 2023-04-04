/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:49:03 by fsoares-          #+#    #+#             */
/*   Updated: 2022/06/01 17:00:46 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define INTERNAL_BUFFER 1024
# define BUILDER_ERROR -1
# define BUILDER_OK 1

t_string	*new_builder(void);
int			append_string(t_string *string, char *str);
char		*free_builder(t_string *builder);
void		my_memmove(char *dest, char *src, size_t n);

#endif