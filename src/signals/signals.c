
#include "signals.h"
#include <signal.h>
#include <../inc/minishell.h>

void sigint_handler(int signum)
{

    (void)signum;
    // TODO: needs cheching if it is executing anything
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
    // printf("Se recibió la señal SIGINT (Ctrl-C)\n");
    // Por ejemplo, detener el proceso actual o realizar alguna limpieza antes de terminar

}

// Manejador de señal para EOF (Ctrl-D)
void eof_handler(int signum)
{
    (void)signum;
    printf("Se recibió la señal de EOF (Ctrl-D)\n");
    // Por ejemplo, finalizar la lectura o el programa que está esperando la entrada
}

// Manejador de señal para SIGQUIT (Ctrl-\)
void sigquit_handler(int signum)
{
    (void)signum;
    printf("Se recibió la señal SIGQUIT (Ctrl-\\)\n");
    // Por ejemplo, finalizar el proceso actual o generar un volcado de núcleo
}

void signals(void)
{
	signal(SIGINT, sigint_handler);   // Manejador para SIGINT (Ctrl-C)
    signal(SIGQUIT, sigquit_handler); // Manejador para SIGQUIT (Ctrl-\)
    signal(SIGTSTP, SIG_IGN);         // Ignorar la señal SIGTSTP (Ctrl-Z)
}