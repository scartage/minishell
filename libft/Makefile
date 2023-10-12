# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 18:02:58 by fsoares-          #+#    #+#              #
#    Updated: 2023/10/12 19:34:45 by fsoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			  ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
			  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			  ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
			  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
			  ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
			  ft_toupper.c ft_strrev.c

BONUS_SRCS	= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			  ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

EXTRA_SRCS	= ft_atol.c ft_free_split.c protected_calloc.c to_case_str.c \
			  unquote.c ft_atof.c str_helpers.c ft_lstremove.c

GNL_SRCS	= get_next_line.c get_next_line_utils.c

PRINT_SRCS	= flags.c ft_printf.c nbr_formatter.c nbr_to_str.c numbers.c \
			  strings.c writer.c

LIB_SRCS	= $(SRCS) $(BONUS_SRCS) $(EXTRA_SRCS) $(GNL_SRCS) $(PRINT_SRCS)

OBJS_DIR	= obj
LIB_OBJS	= $(addprefix  $(OBJS_DIR)/, $(LIB_SRCS:.c=.o))
LIB_DEPS	= $(addprefix  $(OBJS_DIR)/, $(LIB_SRCS:.c=.d))

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD -g
NAME		= libft.a

vpath %.c src/base src/extra src/gnl src/printf
vpath %.h src src/base src/extra src/gnl src/printf

.SECONDEXPANSION:

green := $(shell tput setaf 2)
nc := $(shell tput sgr0)

all: 	$(NAME)

$(OBJS_DIR)/%.o: %.c | $$(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(LIB_DEPS)
$(NAME):	$(LIB_OBJS)
	@ar rc $(NAME) $(LIB_OBJS)
	@echo "$(green)libft compiled$(nc)"

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

.PHONY: all clean fclean re bonus
