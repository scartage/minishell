CFLAGS		= -Wall -Werror -Wextra -MMD -g -fsanitize=address -fsanitize=undefined

all:
	make -C ..
	rm -f ../obj/main.o
	gcc $(CFLAGS) -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -L../libft -lft -I../libft token_tester.c ../obj/*