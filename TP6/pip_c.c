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

void pip_c(void){
    //Variables
    int tube[2];
    char * msg_fils = "Je suis le fils 1 et je transmets ce message à mon frère";
    //char * msg_pere = "Je suis le père et mes fils se sont terminés avec les codes :  ... et ...";
    char msg[256];
    int status_1=0, status_2=0;
    pid_t pid_1,pid_2;

    //creation pipe
    CHK(pipe(tube));

    //fork
    CHK(pid_1 = fork());

    // 
    switch (pid_1){
    case -1 : raler("fork");
        break; 
    case 0 : //fils_1
        CHK(close(tube[0]));
        CHK(write(tube[1],msg_fils, strlen(msg_fils)));
        CHK(close(tube[1]));
        exit(EXIT_SUCCESS);
    }

    CHK(pid_2 = fork());

    switch (pid_2){
        case -1 : raler("fork");
            break; 
        case 0 : //fils 
            CHK(close(tube[1]));
            CHK(read(tube[0],msg, 256));
            printf("Dans fils 2 : %s\n",msg);
            CHK(close(tube[0]));
            exit(EXIT_SUCCESS);
    }

    // pere 
    CHK(close(tube[0]));
    CHK(close(tube[1]));
    CHK(waitpid(pid_1,&status_1,0));
    CHK(waitpid(pid_2,&status_2,0));
    printf("Je suis le père et mes fils se sont terminés avec les codes :  %d et %d\n", status_1, status_2);
    exit(EXIT_SUCCESS);
}


int main(void){
    // if(argc<1){
    //      exit(EXIT_FAILURE);
    // }
    pip_c();
    exit(EXIT_SUCCESS);
}