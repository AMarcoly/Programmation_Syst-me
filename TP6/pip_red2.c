#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
//#include <u.h>
//#include <libc.h>

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

void pip_red2(char * arguments){
    int tube12[2];
    int tube23[2];
    pid_t pid_fils1;
    pid_t pid_fils2;
    pid_t pid_fils3;
    int raison1, raison2,raison3;

    // 1er tube
    CHK(pipe(tube12));

    // fork
    CHK(pid_fils1=fork());
    switch (pid_fils1){
    case -1:
        raler("fork");
        break;
    case 0 : //fils 1
        //fermeture tube en lecture
        //printf("Fils1");
        CHK(close(tube12[0]));
        CHK(dup2(tube12[1],STDOUT_FILENO));
        CHK(close(tube12[1]));
        execlp("ps","ps","eaux",NULL);
        exit(EXIT_SUCCESS);
    }

    //besoin des deux pipes
    CHK(pipe(tube23));
    //fork
    CHK(pid_fils2=fork());

    switch (pid_fils2)
    {
    case -1: 
        raler("fork");
        break;
    case 0: //fils 2
        //printf("Fils2");
        CHK(close(tube12[1]));
        CHK(close(tube23[0]));

        CHK(dup2(tube12[0],STDIN_FILENO));
        CHK(dup2(tube23[1],STDOUT_FILENO));

        CHK(close(tube12[0]));
        CHK(close(tube23[1]));
        
        if(arguments == NULL){
            execlp("grep","grep","^marcolyantoine",NULL);
        }
        else{
            execlp("grep","grep",strcat("^",(char *)arguments),NULL);
<<<<<<< HEAD
        }
            
            
=======
        }     
>>>>>>> d1e369ae84462b1c372c3db1f2dddca188ef36e7
        exit(EXIT_SUCCESS);
    }


    // fils 3

    CHK(pid_fils3=fork());

    switch (pid_fils3)
    {
    case -1:
        raler("fork");
        break;
    case 0: //fils3
        //fermeture complete tube 1 et ecriture tube 2
        //printf("Fils3");
        CHK(close(tube12[0]));
        CHK(close(tube12[1]));
        CHK(close(tube23[1]));

        CHK(dup2(tube23[0],STDIN_FILENO));
        
        CHK(close(tube23[0]));

        execlp("wc","wc","-l",NULL);
        exit(EXIT_SUCCESS);
    }

    //pere
    CHK(close(tube12[0]));
    CHK(close(tube12[1]));
    CHK(close(tube23[0]));
    CHK(close(tube23[1])); 
    
    CHK(wait(&raison1));
    CHK(wait(&raison2));
    CHK(wait(&raison3));
    printf("\tJe suis le pere et mes 3 fils ont fini\n");
}

int main(int argc, char * argv[]){
    if(argc<1){
        exit(EXIT_FAILURE);
    }
    if (argc==1){
        pip_red2(NULL);
    }
        

    if(argc == 2)
        pip_red2(argv[1]);

    exit(EXIT_SUCCESS);
}
