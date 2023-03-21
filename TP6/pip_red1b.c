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

/**
 * @brief Fils execute ls et le pere wc
 * 
 */
void pip_red2(){
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
            //fermeture lecture car on va ecrire
            CHK(close(fd[0]));
            dup2(fd[1], STDOUT_FILENO);
            CHK(close(fd[1]));
            execlp("ls", "ls","-l",NULL);
            exit(0);
    }

    //le pere
    //fermeture en ecriture
    wait(NULL);
    CHK(close(fd[1]));
    dup2(fd[0], STDIN_FILENO);
    CHK(close(fd[0]));
    execlp("wc", "wc","-l",NULL);

}


int main(void){

    pip_red2();
    exit(EXIT_SUCCESS);
}

