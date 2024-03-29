/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:49:47 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 20:50:43 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "errors/errors.h"

/*DO NOT COMMENT THIS FN ITS IMPORTANT*/
char	*get_type(t_token_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR)
		return ("REDIR");
	else
		return ("ARG");
}

// void	printingBefore(t_list *temp_tokens)
// {
// 	t_token *token;
// 	/*while para verificar tokens de la lista*/
// 	printf("---before env_parsing---\n");
// 	if (temp_tokens == NULL)
// 	{
// 		printf("No correct input\n");
// 		return ;
// 	}
// 	while (temp_tokens != NULL)
// 	{
// 		token = temp_tokens->content;
// 		printf("token: [%s]\n", token->value);
// 		temp_tokens = temp_tokens->next;
// 	}
// 	printf("---Go to replace the env_vars---");
// 	printf("\n");
// }
// void printAfter(t_list *temp_tokens)
// {
// 	t_token *token;
// 	printf("---after env_replacing---\n");
// 	while (temp_tokens != NULL)
// 	{
// 		token = temp_tokens->content;
// 		printf("new token content: [%s] type: %s\n", 
// 				token->value, get_type(token->type));
// 		temp_tokens = temp_tokens->next;
// 	}
// 	printf("fins ara\n");
// }

// void print_infile(void *content2)
// {
// 	t_in_file *content = (t_in_file *)content2;
// 	printf("{%s: \"%s\"}, ", 
// 		content->type == HEREDOC ? "<<" : "<", content->name);
// }

// void print_outfile(void *content2)
// {
// 	t_out_file *content = (t_out_file *)content2;
// 	printf("{%s: \"%s\"}, ", 
// 		content->type == WRITE ? ">" : ">>", content->name);
// }

// void print_strings(void *str)
// {
// 	printf("\"%s\", ", (char *)str);
// }
// void print_strings_echo(void *str)
// {
// 	printf("%s ", (char *)str);
// }

// void print_command(void *command2)
// {
// 	t_command *command = (t_command *)command2;
// 	printf("command: {\n");
// 	printf("  in_files: [");
// 	ft_lstiter(command->input_files, print_infile);
// 	printf("]\n  out_files: [");
// 	ft_lstiter(command->output_files, print_outfile);
// 	printf("]\n  arguments: [");
// 	ft_lstiter(command->arguments, print_strings);
// 	printf("]\n}\n");
// }
