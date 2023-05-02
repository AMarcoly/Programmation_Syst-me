#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define CHK(op) do { if ( (op) == -1) raler (#op);  } while(0)

#define MSG "Signal bien recu"

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
    (void)num_sig;
    CHK(write(STDOUT_FILENO,MSG,strlen(MSG)));
}

int main(){
  

}
