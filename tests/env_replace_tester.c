#include <stdio.h>
#include <strings.h>
#include "../inc/minishell.h"
#include "libft.h"
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../src/env_parser/env_parser.h"
// #include "../src/env_replacer/env_replacer.h" // change this to the correct one

extern t_shell g_shell;

char *env_replacer(char *str);

void set_last_exec_result(int res) {
	g_shell.last_execution = res;
}

int test_env_rep(char* replacements, char*input, char* expected) {
	static int test_n = 1;

	if (replacements) {
		char ** envs = ft_split(replacements, ',');
		g_shell.env_variables = env_parser(envs);
		ft_free_split(envs);
	}
	else
		g_shell.env_variables = NULL;

	int res = 1;
	char *actual = env_replacer(input); 
	if (strcmp(actual, expected) != 0)
	{
		printf(RED "Error" NC ": input: %-20s, expected: %-20s, got: %-20s\n", input, expected, actual);
		res = 0;
	} else {
		printf(GRN "Pass " NC ": input: %-20s, expected: %-20s, got: %-20s\n", input, expected, actual);	
	}
	free(actual);
	test_n++;
	return res;
}

int main() {
	printf(CYN "Test: Env Replacer\n" NC);
	bool res = true;

	res = test_env_rep(NULL, "abc", "abc") && res;
	res = test_env_rep(NULL, "a'b'c", "abc") && res;
	res = test_env_rep(NULL, "a\"b\"c", "abc") && res;
	res = test_env_rep(NULL, "a'\"b\"'c", "a\"b\"c") && res;
	res = test_env_rep(NULL, "a\"'b'\"c", "a'b'c") && res;
	res = test_env_rep(NULL, "a'\"'b'\"'c", "a\"b\"c") && res;
	res = test_env_rep(NULL, "'abc'", "abc") && res;
	res = test_env_rep(NULL, "\"abc\"", "abc") && res;

	res = test_env_rep("teste=123",	"abc$teste", "abc123") && res;
	res = test_env_rep("teste=123",	"\"$teste\"", "123") && res;
	res = test_env_rep("test=123",	"abc$teste", "abc") && res;
	res = test_env_rep(NULL,		"abc$teste", "abc") && res;
	res = test_env_rep("teste=123",	"abc$Teste", "abc") && res;

	res = test_env_rep("teste=123,xxx=56", 	"abc$teste$xxx", 	"abc12356") && res;
	res = test_env_rep("Test_123X=123", 	"abc$Test_123X", 	"abc123") && res;
	res = test_env_rep("Test=", 			"abc-$Test-", 		"abc--") && res;

	res = test_env_rep("teste=123", "abc\"$teste,fgt\"xxx", 	"abc123,ftgxxx") && res;
	res = test_env_rep("teste=123", "abc'$teste'xxx", 			"abc$testexxx") && res;
	res = test_env_rep("teste=123", "abc\"xx'$teste'\"xxx", 	"abcxx'123'xxx") && res;
	res = test_env_rep("teste=123", "abc'\"$teste\"yy'xxx", 	"abc\"$teste\"yyxxx") && res;

	set_last_exec_result(0); // cambia el valor en la variable global
	res = test_env_rep("NULL", "res: $?", "res: 0") && res;

	set_last_exec_result(123);
	res = test_env_rep("NULL", 		"res: $?", 			"res: 123") && res;
	res = test_env_rep("NULL", 		"res: $?abc", 		"res: 123abc") && res;
	res = test_env_rep("teste=123", "res: $teste?abc", 	"res: 123?abc") && res;
	res = test_env_rep("teste=123", "res: $test?abc", 	"res: ?abc") && res;

	if (res)
		printf(CYN "Env Replacer " GRN "Tests Passed\n" NC);
	else
		printf(CYN "Env Replacer " RED "Tests Failed\n" NC);
}
