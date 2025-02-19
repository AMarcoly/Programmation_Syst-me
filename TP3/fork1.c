#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
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

void fork_1(){
    int raison;
    pid_t pid,pid_fils;
    //int v;
    pid=fork();
    switch (pid) {
        case -1 : 
            raler(1,"fork");
        break;
        case 0 :
            pid_fils = getpid();
            printf("Je suis le fils de PID %d et mon pere est le processus %d de PID \n",pid_fils,getppid());
            exit(pid_fils % 10);
        break;
        default :
            wait(&raison);
            printf("Je suis le pere et mon PID est: %d\n",getpid());
            printf("Le dernier numero du fils est %d\n",WSTOPSIG(raison));
        break;
        
        /*
        if(wait(&raison)==-1){
            raler(1,"wait");
        }
        if(WIFEXITED(raison)){
            printf("exit(%d)\n",WEXITSTATUS(raison));
        }
        else if(WIFSIGNALED(raison)){
            printf("signal %d\n",WTERMSIG(raison));
        }
        */
    }
}

int main(void){
    
    fork_1();
    exit(EXIT_SUCCESS);
}