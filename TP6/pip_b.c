
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define CHK(op) do { if ( (op) == -1) raler (#op);  } while(0)
#define CHK2(op) do { if ( (op) == NULL) raler (#op);  } while(0)


/**
 * @brief Fonction raler qui va s'occuper d'afficher les erreurs sur la sortie erreur standard
 * 
 * @param msg 
 */

void raler(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


void pipe_b(){
    int tube[2];
    char * message_t = "Je suis le fils et je transmets ce message à mon père";
    char msg[256];

    pid_t pid;
    // faire pipe avant fork
    CHK(pipe(tube));

    pid = fork();

    switch(pid){
    case -1: raler("fork");
        break;
    case 0: //fils
        CHK(close(tube[0]));
        CHK(write(tube[1],message_t, strlen(message_t)));
        CHK(close(tube[1]));
        exit(0);
    }

    // pere 
    wait(NULL);
    CHK(close(tube[1]));
    CHK(read(tube[0], msg, 256));
    CHK(close(tube[0]));
    printf("%s\n",msg);
}


int main(void){
    // if(argc<1){
    //     exit(EXIT_FAILURE);
    // }
    pipe_b();
    exit(EXIT_SUCCESS);
}