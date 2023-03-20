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
 * @brief pere cree deux fils : fils 1 fait ls -l et fils 2 wc -l
 * 
 */
void pip_red3(){
    //creation fils 1
    int fd[2];
    pid_t pid_1,pid_2;
    int status_1,status_2;

    CHK(pipe(fd));

    pid_1 = fork();

    switch(pid_1){
        case -1: perror("fork");
            exit(EXIT_FAILURE);
        case 0: //le filsn1
            close(fd[0]);//ferme extremite en lecture
            dup2(fd[1],1);//pour rester posix sinon (dup2(fd[0],0))
            close(fd[1]);
            execlp("ls","ls","-l",NULL);//ne pas oublier le null
            exit(EXIT_SUCCESS);


    }

    //pere
    //creation nouveau fils
    pid_2=fork();

    switch(pid_2){
        case -1: perror("fork");
            exit(EXIT_FAILURE);
        case 0: //le filsn1
            close(fd[1]);//ferme extremite en ecriture
            dup2(fd[0],0);//pour rester posix sinon (dup2(fd[0],0))
            close(fd[0]);
            execlp("wc","wc","-l",NULL);//ne pas oublier le null
            exit(EXIT_SUCCESS);

    }

    //pere
    close(fd[0]); //fermer extremite lecture
    close(fd[1]);
    waitpid(pid_1,&status_1,0);
    waitpid(pid_2,&status_2,0);
    
    printf("Mes fils se sont bien terminé\n");
    

}




int main(void){
    // if(argc<1){
    //     exit(EXIT_FAILURE);
    // }
    pip_red3();
    exit(EXIT_SUCCESS);
}
