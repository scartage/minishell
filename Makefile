# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scartage <scartage@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 20:31:49 by scartage          #+#    #+#              #
#    Updated: 2023/03/28 20:46:21 by scartage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

INCLUDES = inc/minishell.h

SRCS = main.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

vpath %.c src

$(OBJ_DIR)/%.o: %.c $(INCLUDES) Makefile
		$(CC) $(CFLAGS) -c $< -o $@

all: make_dir $(NAME)

make_dir:
		@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(INCLUDES)
		$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
