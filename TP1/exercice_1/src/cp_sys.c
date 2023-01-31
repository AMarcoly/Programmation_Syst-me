/**
 * @file main.c
 * @author Marcoly ANTOINE (marcoly.antoine@etu.unistra.fr)
 * @brief Fichier main 
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include "../include/raler.h"

/**
 * @brief Fonction qui prend en parametres deux noms de fichiers
 * et recopie le contenu du premier dans le second octet par octet
 * @param fichiersrc 
 * @param fichierdest 
 */
void cp_sys(const char *fichiersrc, const char *fichierdest ){
    int src,dest;   //va recuperer les fd des fonctions open
    ssize_t n; 
    char c; //caractere lire octet par octet

    //ouverture en lecture seule du premier fichier
    CHK( src = open(fichiersrc,O_RDONLY));

    //ouverture en ecriture seule, si le fichier n'existe pas on va le creer avec droits 0666
    CHK(dest=open(fichierdest,O_WRONLY | O_CREAT ));

    //boucle de lecture octet par octet
    while( (n = read(src,&c,1)) > 0 )
        if ( write (dest,&c,1) == -1) //verifier si prob a l'ecriture
            raler(1,"write");
    //si prob a la lecture
    if(n == -1)
        raler(1,"read");

    CHK(close(src)); //fermeture du fichier source
    CHK(close(dest)); //fermeture du fichier destination
}

int main(int argc, char * argv[]){

    //test du nombre d'arguments
    if( argc != 3){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //Appel de la fonction copie
    cp_sys(argv[1],argv[2]);
    return 0;
}