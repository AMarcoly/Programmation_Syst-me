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

void pip_red1(){
    // creation pipe
    int fd[2];

    //declaration pid
    pid_t pid;

    //Faire le pipe avant le fork !!!!!!!!!!
    if(pipe(fd) == -1)
        raler("pipe");

    pid=fork();

    switch (pid) {
        case -1 : raler("fork");
        case 0 :
            //fermeture ecriture
            CHK(close(fd[1]));
            
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execlp("wc", "wc","-l",NULL);
    }

    //le pere
    //fermeture en lecture
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execlp("ls", "ls","-l",NULL);
}


int main(int argc, char *argv[]){

    pip_red1();
    exit(EXIT_SUCCESS);
}

