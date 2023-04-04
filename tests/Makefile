
all:
	make -C ..
	rm -f ../obj/main.o
	gcc -g -fsanitize=address -fsanitize=undefined -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -L../libft -lft -I../libft token_tester.c ../obj/*