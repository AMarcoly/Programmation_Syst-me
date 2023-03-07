#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHK(op) do { if ( (op) == -1) raler (1,#op);  } while(0)


noreturn void raler(int syserr,  const char *msg, ...){
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr,msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    if(syserr == 1)
        perror("");

    exit(EXIT_FAILURE);
}

int fork_2(int n){
    int i;
    pid_t pid,pid_fils;
    int status;

    //lancer les 5 processus fils
    for(i=0; i<n;i++){
        pid= fork();

        if(pid==0){
            printf("Processus fils %03d (PID %d) demare.\n",i,getpid());
            exit(i);
        }else if(pid<0){
            printf("Erreur de fork()\n");
            exit(EXIT_FAILURE);
        }
    }

    //attente terminaison
    for(i=0;i<n;i++){
        pid_fils=wait(&status);
        printf("Processus fils %03d (PID %d) termine avec le code de retour %d.\n",i,pid_fils,WEXITSTATUS(status));
    }
    exit(EXIT_SUCCESS);
}
int main(const int argc , char * argv[]){
    
    fork_2(5);
    exit(EXIT_SUCCESS);
}