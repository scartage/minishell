# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 20:31:49 by scartage          #+#    #+#              #
#    Updated: 2023/04/04 18:28:20 by fsoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -MMD -fsanitize=address -fsanitize=undefined -g
RM			= rm -f

INCLUDES	= inc/minishell.h

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -Llibft -lft
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include -Ilibft

SRCS		= main.c ft_readline.c token_parser.c

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix  $(OBJS_DIR)/, $(SRCS:.c=.d))

LIBFT		= libft/libft.a

vpath %.c src src/parsing

green := $(shell tput setaf 2)
nc := $(shell tput sgr0)

$(OBJ_DIR)/%.o: %.c Makefile
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all: make_dir make_libs $(NAME)

make_libs:
	@$(MAKE) -s -C libft

make_dir:
		@mkdir -p $(OBJ_DIR)

-include $(DEPS)
$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
		@echo "$(green)$(NAME) compiled$(nc)"

clean:
	@$(MAKE) -C libft fclean
	$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
