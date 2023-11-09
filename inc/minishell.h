/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:01 by scartage          #+#    #+#             */
/*   Updated: 2023/11/09 20:53:53 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>				//para el write, isatty
# include <stdlib.h>				//para el exit
# include <stdbool.h>				//para bool
# include <readline/readline.h>		//para obtener input
# include <readline/history.h>		//historial del input
# include "../libft/libft.h"		//para el t_list
# include <signal.h>

# define IS_TEST 0

typedef enum e_token_type {
	ARGUMENT,
	REDIR,
	PIPE
}	t_token_type;

typedef struct s_token {
	char			*value;
	t_token_type	type;
}	t_token;

typedef enum e_in_type {
	NORMAL,
	HEREDOC,
}	t_in_type;

typedef struct s_in_file {
	char		*name;
	t_in_type	type;
	char		*end_str;
}	t_in_file;

typedef enum e_out_type {
	WRITE,
	APPEND,
}	t_out_type;

typedef struct s_out_file {
	char		*name;
	t_out_type	type;
}	t_out_file;

typedef struct s_command {
	t_list	*input_files;
	t_list	*output_files;
	t_list	*arguments;
}	t_command;

typedef struct s_shell {
	t_list	*env_variables;
	t_list	*parsed_words;
}	t_shell;

typedef enum e_state
{
	in_space,
	in_token,
	in_quote,
	in_word,
	in_single_quote,
	in_double_quote,
	in_env_var_name,
}	t_state;

char	*get_input(int exit_status);

#endif
