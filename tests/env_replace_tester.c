int test_env_rep(char* replacements, char*input, char* expected) {

	g_shell.envs = replacemnets;

	char *res = replace_env(input);
	if (strcmp(res, expected) != 0) {
		printf("Not the same")
	}
}

int main() {
	test_env_rep(NULL, "abc", "abc");
	test_env_rep(NULL, "a'b'c", "abc");
	test_env_rep(NULL, "a\"b\"c", "abc");
	test_env_rep(NULL, "a'\"b\"'c", "a\"b\"c");
	test_env_rep(NULL, "a\"'b'\"c", "a'b'c");
	test_env_rep(NULL, "a'\"'b'\"'c", "a\"b\"c");
	test_env_rep(NULL, "'abc'", "abc");
	test_env_rep(NULL, "\"abc\"", "abc");

	test_env_rep("teste=123", "abc$teste", "abc123");
	test_env_rep("test=123", "abc$teste", "abc");
	test_env_rep(NULL, "abc$teste", "abc");
	test_env_rep("teste=123", "abc$Teste", "abc");

	test_env_rep("teste=123,xxx=56", "abc$teste$xxx", "abc12356");
	test_env_rep("Test_123X=123", "abc$Test_123X", "abc123");
	test_env_rep("Test=", "abc-$Test-", "abc--");

	test_env_rep("teste=123", "abc\"$teste,fgt\"xxx", "abc123,ftgxxx");
	test_env_rep("teste=123", "abc'$teste'xxx", "abc$testexxx");
	test_env_rep("teste=123", "abc\"xx'$teste'\"xxx", "abcxx'123'xxx");
	test_env_rep("teste=123", "abc'\"$teste\"yy'xxx", "abc\"$teste\"yyxxx");

	set_last_exec_result(0); // cambia el valor en la variable global
	test_env_rep("NULL", "res: $?", "res: 0");

	set_last_exec_result(123);
	test_env_rep("NULL", "res: $?", "res: 123");
	test_env_rep("NULL", "res: $?abc", "res: 123abc");
	test_env_rep("teste=123", "res: $teste?abc", "res: 123?abc");
}
