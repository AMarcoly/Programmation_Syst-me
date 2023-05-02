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
    
    
    sigset_t new,old;

    // sigaction 
    struct sigaction s;
    s.sa_handler = f;
    s.sa_flags =0;
    sigemptyset(&s.sa_mask);

    if(sigaction(SIGINT,&s,NULL)==-1) raler("Sigaction");

    sleep(3);

    // mask
    sigemptyset(&new);
    sigaddset(&new,SIGINT);
    sigprocmask(SIG_BLOCK,&new,&old);

    //
    sleep(3);

   sigprocmask(SIG_SETMASK,&new,&old);

   //
   sleep(3);

   exit(EXIT_SUCCESS);


}
