#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signal) {
    if (signal == SIGINT) {
        printf("haha, fuck you, I wont close.\n");
    }
}

int main() {
    signal(SIGINT, signal_handler);
    while (1)
        sleep(10000);
}