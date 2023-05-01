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

void f(int sig){
    (void)sig;
    ssize_t n;
    char buf[256] = "J'ai reçu un signal\n";
    n = write(STDOUT_FILENO,buf,strlen(buf));
    if(n==-1) raler("write");
}

void ecoute_active(){
    struct sigaction s;
    s.sa_handler = f;
    s.sa_flags=0;
    sigaction(SIGUSR1,&s,NULL);

    while(1);
}

int main(){
    ecoute_active();

    exit(EXIT_SUCCESS);
}