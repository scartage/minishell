
#include "signals.h"
#include <signal.h>
#include <../inc/minishell.h>
#include <unistd.h>

// SIGINT => control + C
void	signal_handler_input(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

// does nothing. The builtin functionality already handles this case
// by propagating the signal down
void	signal_handler_executing(int signal)
{
	(void)signal;
}

void	set_signal_handler(void (handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

/*info interesante
https://github.com/DimitriDaSilva/42_minishell#4-termcaps*/