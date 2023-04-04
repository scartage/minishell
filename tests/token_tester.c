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
	printf("En el teste %i\n", test_n);
	t_list *result = parse_line(line);
	while (*expected) {
		if (strcmp(*expected, result->content) != 0) {
			printf("Error: expected: -%s-, got -%s-\n", *expected, result->content);
			return false;
		}
		result = result->next;
		expected++;
	}
	test_n++;
	return true;
}

int main() {
	printf(CYN "Tests token parser\n" NC);
	bool res = true;
	
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
		printf(GRN "Tests Passed\n" NC);
	else
		printf(RED "Tests Failed\n" NC);
}