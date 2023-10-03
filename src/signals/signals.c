
#include "signals.h"
#include <signal.h>
#include <../inc/minishell.h>
#include <unistd.h>

static void signal_handler(int signal)
{
    if (signal == SIGINT)       //control + C
    {
        write(STDOUT_FILENO, "\n", 1);    
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (signal == SIGQUIT) //cntrl + D (sin proceso en ejecucion)
    {
        rl_redisplay();     //aqui no deberia hacer nada, funciona cuando
                            //hay algo en ejecucion
    }
    return ;
}

static void child_handler(int signal)
{
    if (signal == SIGINT)
    {
        fflush(stdout);
        write(STDOUT_FILENO, "\n", 1);    
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
        exit(EXIT_SUCCESS);
    }
    else if (signal == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        rl_replace_line("", 1);
        rl_on_new_line();
        rl_redisplay();
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