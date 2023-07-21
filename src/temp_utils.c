#include "../inc/minishell.h"

void printingBefore(t_list *temp_tokens)
{
	/*while para verificar tokens de la lista*/
	printf("---before env_parsing---\n");
	if (temp_tokens->content == NULL)
	{
		printf("No correct input\n");
		return ;
	}
	while (temp_tokens->content != NULL)
	{
		printf("token: [%s]\n", (char *)temp_tokens->content);
		if (temp_tokens->next == NULL)
			break;
		temp_tokens = temp_tokens->next;
	}
	printf("---Go to replace the env_vars---");
	printf("\n");
}

void printAfter(t_list *temp_tokens)
{
	printf("---after env_replacing---\n");
	while (temp_tokens->content != NULL)
	{
		printf("new token content: [%s]\n", (char *)temp_tokens->content);
		if (temp_tokens->next == NULL)
			break;
		temp_tokens = temp_tokens->next;
	}
	printf("fins ara\n");	
}

void print_infile(void * content2) {
	t_in_file * content = (t_in_file *)content2;
	printf("{%s: \"%s\"}, ", content->type == HEREDOC ? "<<" : "<", content->name);
}

void print_outfile(void * content2) {
	t_out_file * content = (t_out_file *)content2;
	printf("{%s: \"%s\"}, ", content->type == WRITE ? ">" : ">>", content->name);
}

void print_strings(void * str) {
	printf("\"%s\", ", (char *)str);
}
void print_strings_echo(void * str) {
	printf("%s ", (char *)str);
}

/*TO CHECK
	quiero evaular los argumentos que le llegan a exit, solo pueden ser INTS (numericos??)*/
void ft_isdigit_void(void *str)
{
	char * tmp = ft_strdup(str);
	ft_isdigit(tmp[0]);
}

void print_command(void * command2) {
	t_command * command = (t_command *)command2;
	printf("command: {\n");
	printf("  in_files: [");
	ft_lstiter(command->input_files, print_infile);
	printf("]\n  out_files: [");
	ft_lstiter(command->output_files, print_outfile);
	printf("]\n  arguments: [");
	ft_lstiter(command->arguments, print_strings);
	printf("]\n}\n");
}