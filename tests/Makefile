CFLAGS		= -Wall -Werror -Wextra -MMD -g -fsanitize=address -fsanitize=undefined

OBJS = $(filter-out ../obj/main.o, $(wildcard ../obj/*.o))

BASE_CC	= gcc $(CFLAGS) -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -L../libft -lft -I../libft $(OBJS)

all: $(OBJS)
	@$(MAKE) --no-print-directory -C ..
	@$(BASE_CC) token_tester.c -o token_tester.out
	$(BASE_CC) env_replace_tester.c -o env_replace_tester.out
	./token_tester.out
	./env_replace_tester.out
