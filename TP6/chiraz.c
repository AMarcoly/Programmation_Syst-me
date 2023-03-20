#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>




//Le programme crée trois processus fils ; 
//chaque processus fils exécute une commande. 
//Après la création des fils, le père attend leur terminaison.
//Le nom sera donné par l’utilisateur en argument du programme, ou prendra la valeur de la variable d’environnement USER par défaut.

int raler(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

//je veux 3 fils 
//ya deux pipe
//ps eaux |
// grep "ˆ<nom>" | 
//wc -l

int main()
{
    int pid1, pid2, pid3; // t pas oubliger 3 mais c'est plus claire
    int raison1,raison2,raison3;
    int fd12[2],fd23[2];


    if(pipe(fd12)==-1) raler("pipe1");
   
    //creation du fils1 pour ps eaux ecrit 1 out 
    switch(pid1=fork())
    {
    case -1:
        raler("fork1");
        break;
    case 0:
        if(close(fd12[0])==-1)raler("close fd120");//fermer la lecture du premier pipe
        if(dup2(fd12[1],STDOUT_FILENO)==-1)raler("dup2 fd12");//redirige la sortie standard vers lecriture pipe
        if(close(fd12[1])==-1) raler("close fd12 1 ps");
        execlp("ps","ps","eaux",NULL);
        raler("exclp ps");
        printf("fils1\n");
        exit(EXIT_SUCCESS);
        
    }

    
     if(pipe(fd23)==-1) raler("pipe1");
    //creation fils2 pour grep USER qui lit 0 in ds le tube fd12 et ecrit dans le fd23 1 out
    switch(pid2=fork())
    {
    case -1:
        raler("fork2");
        break;
    case 0:
        if(close(fd12[1])==-1)raler("close fd120");//fermer ecriture fd12
        if(close(fd23[0])==-1)raler("close fd120");//fermer ecriture fd12
        
        if(dup2(fd12[0],STDIN_FILENO)==-1)raler("dup2 fd12");//redirige entree strandard vers lecture de fd12
        if(dup2(fd23[1],STDOUT_FILENO)==-1)raler("dup2 fd23");//redirige sortie standard vers ecriture de fd23

        if(close(fd12[0])==-1) raler("close fd12 0 grep");
        if(close(fd23[1])==-1) raler("close fd23 1 grep");
        execlp("grep","grep", "^marcolyantoine",NULL);
        raler("exclp grep");
        printf("fils2\n");
        exit(EXIT_SUCCESS);
    }
    


    
   
    //creation du fils 3 pour wc -l qui lit fd23 0 in 
    switch (pid3=fork())
    {
    case -1:
        raler("fork3");
        break;
    
    case 0:
        //fermer les pipes
        if(close(fd12[0])==-1) raler("close fd12 0 grep");
        if(close(fd12[1])==-1) raler("close fd12 0 grep");
        if(close(fd23[1])==-1) raler("close fd23 1 grep");
        
        if(dup2(fd23[0],STDIN_FILENO)==-1)raler("dup2 fd23[0] fils3");
        if(close(fd23[0])==-1)raler("close f23[O] fils3");
        execlp("wc","wc","-l",NULL);
        raler("execlp wc fils3");
        printf("fils3\n");
        exit(EXIT_FAILURE);

    }
    
    
    //ferme le premier pipe inutilise pr le per
    if(close(fd12[0])==-1) raler("close");
    if(close(fd12[1])==-1) raler("close");
    if(close(fd23[0])==-1) raler("close");
    if(close(fd23[1])==-1) raler("close");

    if(waitpid(pid1,&raison1,0)==-1) raler("wait");
    if(waitpid(pid2,&raison2,0)==-1) raler("wait");
    if(waitpid(pid3,&raison3,0)==-1) raler("wait");


    printf("mes enfant se sont bien terminé\n");


    return 0;
}