#include <stdio.h>
#include <strings.h>
#include "../src/parsing/token_parser.h"
#include "libft.h"
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

char **arr(int n, ...)
{
	va_list argp;
	char **result = calloc(n + 1, sizeof(char *));

	va_start(argp, n);
	int i;
	for (i = 0; i < n; i++)
		result[i] = va_arg(argp, char *);

	va_end(argp);
	result[i] = NULL;
	return result;
}


bool test_parsing(char *line, char** expected) {
	
	static int test_n = 1;
	char **temp = expected;
	//printf("En el teste %i\n", test_n);
	t_list *result = parse_line(line);
	t_list *tmp_res = result;
	bool test_ok = true;
	while (*expected) {
		if (strcmp(*expected, result->content) != 0) {
			printf(RED "Error" NC ": expected: -%s-, got -%s-\n", *expected, result->content);
			test_ok = false;
		}
		result = result->next;
		expected++;
	}
	if (result != NULL) {
		printf(RED "Error" NC ": has more members than expected: %s", result->content);
		test_ok = false;
	}
	ft_lstclear(&tmp_res, free);
	test_n++;
	free(temp);
	return test_ok;
}

int main() {
	printf(CYN "Test: Token Parser\n" NC);
	bool res = true;

	res = test_parsing("", arr(0)) && res;
	res = test_parsing("    ", arr(0)) && res;
	
	res = test_parsing("abcd", arr(1, "abcd")) && res;
	
	res = test_parsing("\"abcd\"", arr(1, "\"abcd\"")) && res;
	
	res = test_parsing("abcd sdf", arr(2, "abcd", "sdf")) && res;
	
	res = test_parsing("ab\"c d\" sdf", arr(2, "ab\"c d\"", "sdf")) && res;
	
	res = test_parsing("a\"b c\"d sdf    ", arr(2, "a\"b c\"d", "sdf")) && res;
	
	res = test_parsing("a'b c'd sdf    ", arr(2, "a'b c'd", "sdf")) && res;
	
	res = test_parsing("a'b \"c \" d'e", arr(1, "a'b \"c \" d'e")) && res;

	res = test_parsing("aa ||bb", arr(4, "aa", "|", "|", "bb")) && res;
	res = test_parsing("aa||bb", arr(4, "aa", "|", "|", "bb")) && res;
	res = test_parsing("aa| |bb", arr(4, "aa", "|", "|", "bb")) && res;
	res = test_parsing("aa| | bb", arr(4, "aa", "|", "|", "bb")) && res;
	
	res = test_parsing("aa > out", arr(3, "aa", ">", "out")) && res;
	res = test_parsing("aa >out", arr(3, "aa", ">", "out")) && res;
	res = test_parsing("aa> out", arr(3, "aa", ">", "out")) && res;
	res = test_parsing("aa>out", arr(3, "aa", ">", "out")) && res;
	res = test_parsing("'aa>out'", arr(1, "'aa>out'")) && res;
	res = test_parsing("\"aa>out\"", arr(1, "\"aa>out\"")) && res;
	
	res = test_parsing("aa >> out", arr(3, "aa", ">>", "out")) && res;
	res = test_parsing("aa >>out", arr(3, "aa", ">>", "out")) && res;
	res = test_parsing("aa>> out", arr(3, "aa", ">>", "out")) && res;
	res = test_parsing("aa>>out", arr(3, "aa", ">>", "out")) && res;
	res = test_parsing("'aa>>out'", arr(1, "'aa>>out'")) && res;
	
	res = test_parsing("aa < out", arr(3, "aa", "<", "out")) && res;
	res = test_parsing("aa <out", arr(3, "aa", "<", "out")) && res;
	res = test_parsing("aa< out", arr(3, "aa", "<", "out")) && res;
	res = test_parsing("aa<out", arr(3, "aa", "<", "out")) && res;
	res = test_parsing("'aa<out'", arr(1, "'aa<out'")) && res;
	res = test_parsing("\"aa<out\"", arr(1, "\"aa<out\"")) && res;
	
	res = test_parsing("aa << out", arr(3, "aa", "<<", "out")) && res;
	res = test_parsing("aa <<out", arr(3, "aa", "<<", "out")) && res;
	res = test_parsing("aa<< out", arr(3, "aa", "<<", "out")) && res;
	res = test_parsing("aa<<out", arr(3, "aa", "<<", "out")) && res;
	res = test_parsing("'aa<<out'", arr(1, "'aa<<out'")) && res;
	
	res = test_parsing("aa<<<>|>><|out", arr(9, "aa", "<<", "<", ">", "|", ">>", "<", "|", "out")) && res;
	
	res = test_parsing("aa<<<>'|>>'<|out", arr(8, "aa", "<<", "<", ">", "'|>>'", "<", "|", "out")) && res;
	
	res = test_parsing(
		"< bla < otro |e$HASD xxxxx\"$HASD\"xxxxx'$HASD' < other      \"sddggsdgds $? $BLA $BLA2 dfsd\" > salida 'gfd | sgs $BLA $?' | wc -l >> out >out2 > out3", 
		arr(22, "<",
				"bla",
				"<",
				"otro",
				"|",
				"e$HASD",
				"xxxxx\"$HASD\"xxxxx'$HASD'",
				"<",
				"other",
				"\"sddggsdgds $? $BLA $BLA2 dfsd\"",
				">",
				"salida",
				"'gfd | sgs $BLA $?'",
				"|",
				"wc",
				"-l",
				">>",
				"out",
				">",
				"out2",
				">",
				"out3")
	) && res;


	if (res) 
		printf(CYN "Token Parser " GRN "Tests Passed\n" NC);
	else
		printf(CYN "Token Parser " RED "Tests Failed\n" NC);
}