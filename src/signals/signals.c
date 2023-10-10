
#include "signals.h"
#include <signal.h>
#include <../inc/minishell.h>
#include <unistd.h>

extern t_gShell g_shell;

static void signal_handler(int signal)
{
    if (signal == SIGINT)       //control + C
    {
        write(STDOUT_FILENO, "\n", 1);    
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (signal == SIGQUIT) //cntrl + / (sin proceso en ejecucion)
    {
        rl_redisplay();
    }
    return ;
}

static void child_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);    
        exit(EXIT_FAILURE);    }
    else if (signal == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        exit(EXIT_FAILURE);
    }
    return ;
}

void signals(int i)
{
	struct sigaction    sa;

    if (i)
        sa.sa_handler = &signal_handler;
    else
        sa.sa_handler = &child_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

/*info interesante 
https://github.com/DimitriDaSilva/42_minishell#4-termcaps*/