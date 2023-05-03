#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
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

void handler(int sig) {
    (void)sig;
    char buf[256] = "Traitement en cours...\n";
    ssize_t n = write(STDOUT_FILENO,buf ,strlen(buf));
    if(n==-1) raler("write");
}

void usr1_handler(int sig) {
    (void)sig;
    printf("Le processus fils s'est arrêté\n");
    exit(0);
}

int main() {
    pid_t pid;
    int status;
    struct sigaction act_p, act_f, oldact;

    // action fils
    act_f.sa_handler = handler;
    sigemptyset(&act_f.sa_mask);
    act_f.sa_flags = 0;
    CHK(sigaction(SIGALRM, &act_f, &oldact));
    
    // action pere
    act_p.sa_handler = usr1_handler;
    sigemptyset(&act_p.sa_mask);
    act_p.sa_flags = 0;
    CHK(sigaction(SIGUSR1, &act_p, &oldact));
    
    pid = fork();
    if (pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(1);
    } else if (pid == 0) { // Code du processus fils
        while(1) {
            alarm(1); // Lance le minuteur 
            sigsuspend(NULL); // Attends jusqu'à ce qu'un signal soit reçu
        }
    } else { // Code du processus père
        sleep(10); // Attends 10 secondes
        CHK(kill(pid, SIGUSR1)); // Envoie le signal SIGUSR1 au fils
        wait(&status); // Attends la terminaison du fils
    }

    return 0;
}
