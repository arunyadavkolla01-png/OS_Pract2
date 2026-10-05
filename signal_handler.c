#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;
volatile sig_atomic_t sigusr1_received = 0;

void handler(int sig)
{
    if (sig == SIGINT)  sigint_received = 1;
    if (sig == SIGTERM) sigterm_received = 1;
    if (sig == SIGUSR1) sigusr1_received = 1;
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    printf("Signal handling program started.\n");
    printf("Process PID = %d\n", getpid());
    printf("\nSend signals using:\n");
    printf("SIGINT  : kill -SIGINT %d\n", getpid());
    printf("SIGTERM : kill -SIGTERM %d\n", getpid());
    printf("SIGUSR1 : kill -SIGUSR1 %d\n", getpid());

    while (1) {
        pause();
        if (sigint_received) {
            printf("\nSIGINT received!\nInterrupt signal handled.\n");
            sigint_received = 0;
        }
        if (sigusr1_received) {
            printf("SIGUSR1 received!\nUser-defined event handled.\n");
            sigusr1_received = 0;
        }
        if (sigterm_received) {
            printf("SIGTERM received!\nTermination requested.\n");
            break;
        }
    }

    printf("Program terminating gracefully...\n");
    return 0;
}
