#ifndef SIGNALS_H
# define SIGNALS_H

void signals(int i);

void	set_signal_handler(void (*handler)(int));
void	signal_handler_input(int signal);
void	signal_handler_executing(int signal);

#endif