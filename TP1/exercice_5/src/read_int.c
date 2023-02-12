/**
 * @file read_int.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

#include "../include/raler.h"

/**
 * @brief fonction qui prend en parametre un fichier et une position et renvoie l'entier a cette position
 * 
 * @param fichiersrc 
 * @param pos 
 */
void read_int(const char * fichiersrc,int pos){
    //declaration des variables 
    int64_t entier_a_lire; //entier a lire
    int fd_fichier; //file descriptor
    ssize_t taille_du_fichier ;
    struct stat stbuf;  //declaration structure stbuf

    //ouverture du fichier
    CHK(fd_fichier = open(fichiersrc,O_RDONLY));
    
    //recuperation taille du fichier
    CHK(stat(fichiersrc,&stbuf));
    taille_du_fichier=stbuf.st_size;

    //verifier si on ne va pas au-dela de la taille du fichier en positif ou negatif
        //si oui renvoyer message erreur
    if (( 0 < pos ) && (pos > taille_du_fichier)) {
        printf("Vous etes alle au dela de la taille du fichier, pas de caractere ici\n");
        exit(EXIT_FAILURE);
    }
    //sinon
    //placer le curseur a position desire
    CHK(lseek(fd_fichier,pos,SEEK_SET));
    //copie la valeur a cette position
    if(stbuf.st_size < 8)
        printf("Pas assez d'octets\n");
    //lecture des octets
    CHK(read(fd_fichier,&entier_a_lire,1));
    //affichage de l'entier a cette position
    printf("L'entier lu est %ld\n",entier_a_lire);
}


int main(int argc,  char * argv[]){

     //test du nombre d'arguments
    if( argc != 3){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int position = atoi(argv[2]);

    //Appel fonction
    read_int(argv[1],position);
    
    exit(EXIT_SUCCESS);
}