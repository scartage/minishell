
#include "builtins.h"
#include "minishell.h"

t_builtin	get_builtin(t_command *command)
{
	t_builtin	builtins[7];
	int			i;

	builtins[0] = (t_builtin){.name = "echo", .fn = echo};
	builtins[1] = (t_builtin){.name = "pwd", .fn = pwd};
	builtins[2] = (t_builtin){.name = "exit", .fn = ft_exit};

	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(command->arguments->content, builtins[i].name, 20) == 0)
		{
			return (builtins[i]);
		}
		i++;
	}

	return ((t_builtin){.name = NULL, .fn = NULL});
}

int	execute_builtin(t_builtin builtin, t_command *command, t_list *envs)
{
	//FIXME: handle redirections
	return (builtin.fn(command->arguments, envs));
}
