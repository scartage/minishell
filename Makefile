# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 20:31:49 by scartage          #+#    #+#              #
#    Updated: 2023/11/09 20:50:17 by fsoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -MMD -g # -fsanitize=address -fsanitize=undefined
RM			= rm -rf

INCLUDES	= inc/minishell.h

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -Llibft -lft
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include -Ilibft -Iinc

SRCS		= main.c ft_readline.c token_parser.c classifier.c parsing_utils.c in_token_handler.c errors.c \
			  env_parser.c env_replacer.c temp_utils.c signals.c commands.c command_utils.c \
			  builtins.c env_export_unset.c executor.c cd_echo_exit.c file_handler.c \
			  path_handler.c path_handler_utils.c executor_utils.c executor_utils_2.c heredoc.c pipe_handler.c \
			  built_utils.c export_utils.c export_utils_2.c unset_utils.c utils_for_builtins.c \
			  errors_and_utils.c quote_eliminator.c env_utils.c

SRC_DIRS	= parsing errors envs signals builtins executor \
              debug  # remove when to deliver

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

run: all 
	./minishell

.PHONY: all clean fclean re test run
