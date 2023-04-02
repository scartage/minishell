# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scartage <scartage@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 20:31:49 by scartage          #+#    #+#              #
#    Updated: 2023/04/02 18:15:02 by scartage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

INCLUDES = inc/minishell.h

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

SRCS = main.c ft_readline.c utils.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

vpath %.c src

$(OBJ_DIR)/%.o: %.c $(INCLUDES) Makefile
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all: make_dir $(NAME)

make_dir:
		@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(INCLUDES)
		$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
