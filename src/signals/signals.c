
#include "signals.h"
#include <signal.h>
#include <../inc/minishell.h>
#include <unistd.h>

void sigint_handler(int signum)
{
    (void)signum;
    if (g_shell.is_executing)
    {
        // TODO: needs cheching if it is executing anything
        //Cerramos el proceso que esta en ejecucion
        kill(g_shell.children_pid, SIGINT);
    }
    write(STDOUT_FILENO, "\n", 1);    
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
    // Por ejemplo, detener el proceso actual o realizar alguna limpieza antes de terminar
}


// Manejador de señal para SIGQUIT (Ctrl-\)
void sigquit_handler(int signum)
{
    (void)signum;
    if (g_shell.is_executing)
    {
        rl_replace_line("Quit: 3", 1);
        rl_on_new_line();
        rl_redisplay();
        kill(getpid(), SIGQUIT);
    }
}

void signals(void)
{
	signal(SIGINT, sigint_handler);   // Manejador para SIGINT (Ctrl-C)
    signal(SIGQUIT, sigquit_handler); // Manejador para SIGQUIT (Ctrl-\)
}

/*info interesante 
https://github.com/DimitriDaSilva/42_minishell#4-termcaps*/