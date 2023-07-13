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
