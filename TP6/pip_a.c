/**
 * @file pip_a.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

 void pipe_a(){
    //creation processus fils
    // pere envoie dans le tube la chaine "Je suis le pere et je transmets le message a mon fils"
    //le fils recupere le message dans le tube et l'affiche

    //declarations des variables
    int fd[2];
    pid_t pid;
    char buf[64]; //utilisation tableau statique car le pere pointe vers une chaine et le fils vers un autre quand on fait fork
    //strlen(chaine) ne marcherait pas
    char * chaine = "Je suis le pere et je transmets le message a mon fils\n";
    // ouverture du pipe
    if(pipe(fd)== -1)
        raler("pipe");
    
    //fork
    pid=fork();

    //
    switch(pid){
        case -1 : raler("fork");
            break;
        case 0 ://fils
                CHK(close(fd[1])); //fermeture extremite en ecriture
                CHK(read(fd[0], buf, 64));
                CHK(close(fd[0])); // fermeture fd[0] car duplique
                printf("Je suis le fils et j'ai recu : %s\n",buf);
                exit(0);
                break;
    }

    //dans le pere
    
    CHK(close(fd[0])); // fermeture extremite en ecri
    CHK(write(fd[1], chaine,strlen(chaine)));
    CHK(close(fd[1]));
    wait(NULL);

}


int main(){
    // if(argc<1){
    //     exit(EXIT_FAILURE);
    // }
    pipe_a();
    exit(EXIT_SUCCESS);
}