# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scartage <scartage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 20:31:49 by scartage          #+#    #+#              #
#    Updated: 2023/07/13 19:32:32 by scartage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -MMD -g -fsanitize=address -fsanitize=undefined
RM			= rm -rf

INCLUDES	= inc/minishell.h

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -Llibft -lft
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include -Ilibft

SRCS		= main.c ft_readline.c token_parser.c parsing_utils.c in_token_handler.c errors.c \
			  env_parser.c env_replacer.c temp_utils.c 

SRC_DIRS	= parsing errors env_parser env_replacer

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix  $(OBJ_DIR)/, $(SRCS:.c=.d))

LIBFT		= libft/libft.a

vpath %.c src $(addprefix  src/, $(SRC_DIRS))

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
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

test: all
	@$(MAKE) -C tests

.PHONY: all clean fclean re test
