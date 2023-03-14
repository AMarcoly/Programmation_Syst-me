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
    // variables
    int fd1[2];
    int fd2[2];
    int pid;
}