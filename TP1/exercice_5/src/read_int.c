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

    struct stat stbuf;

    //ouverture du fichier
    CHK(fd_fichier = open(fichiersrc,O_RDONLY));
    //recuperation taille du fichier

    CHK(stat(fichiersrc,&stbuf));
    n=stbuf.st_size;
    //verifier si on ne va pas au-dela de la taille du fichier en positif ou negatif
        
    //si oui renvoyer message erreur
    
    //sinon
        //placer le curseur a position desire
       

    //copie la valeur a cette position

    //affichage de l'entier a cette position
}