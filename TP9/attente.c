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

void f(int num_sig){
    dup2(STDERR_FILENO,STDOUT_FILENO);
    psignal(num_sig,"Signal ");
    exit(EXIT_SUCCESS);
}

void attente(){
    struct sigaction s;
    s.sa_handler = f;

    for(int signal=1;signal<32;signal++){
        if((signal != SIGKILL) && (signal!=SIGSTOP)){
            if(sigaction(signal,&s,NULL)==-1) raler("sigaction");
        }
    }

    sigset_t mask;
    if(sigemptyset (&mask) == -1)raler("sigemptyset");

    sigsuspend(&mask);
}

int main(){
    attente();
    exit(EXIT_SUCCESS);
}