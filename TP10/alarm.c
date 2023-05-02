#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define CHK(op) do { if ( (op) == -1) raler (#op);  } while(0)



/**
 * @brief Fonction raler qui va s'occuper d'afficher les erreurs sur la sortie erreur standard
 * 
 * @param msg 
 */

void raler(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MESSAGE "Processus fils\n"

volatile sig_atomic_t stop = 0;

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        write(STDOUT_FILENO, "Signal SIGUSR1 reçu\n", 21);
        stop = 1;
    }
}

int main() {
    pid_t pid;

    struct sigaction action;
    action.sa_handler = handle_signal;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);

    pid = fork();
    if (pid == -1) {
        perror("Erreur fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processus fils
        struct sigaction action_fils;
        action_fils.sa_handler = SIG_IGN; // Ignorer le signal SIGALRM dans le fils
        action_fils.sa_flags = 0;
        sigemptyset(&action_fils.sa_mask);
        sigaction(SIGALRM, &action_fils, NULL);

        while (1) {
            sleep(1);
            write(STDOUT_FILENO, MESSAGE, sizeof(MESSAGE)-1);
        }

        exit(EXIT_SUCCESS);
    } else { // Processus père
        alarm(10);
        sigset_t mask, oldmask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);

        while (!stop) {
            sigsuspend(&mask);
        }

        printf("Fin du processus père\n");
        exit(EXIT_SUCCESS);
    }
}

