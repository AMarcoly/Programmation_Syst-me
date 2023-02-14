/**
 * @file write_int.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/raler.h"

void write_int(char * const fichiersrc,int64_t nbr, int pos){
    //variables
    int fd;
    struct stat st_buf;
    ssize_t taille_du_fichier;
    char c_vide = 0;

    //ouverture fichier en ecriture avec permission standard
    CHK(fd= open(fichiersrc,O_WRONLY|O_CREAT,0666));
    //recuperation information du fichier
    CHK(stat(fichiersrc,&st_buf));
    //taille du fichier
    taille_du_fichier = st_buf.st_size;//recuperation taille du fichier
    //ecriture

    //si pos neg choix de le ramener a zero. Choix d'implementation
    if(pos < 0){
        pos = 0;
    }
    if(pos > taille_du_fichier){
        for(int i= taille_du_fichier+1; i<pos;i++){
            CHK(write(fd, &c_vide, 1));
        }
    }

    //placer le curseur a la bonne position
    CHK(lseek(fd,pos,SEEK_SET));
    //ecriture caractere
    CHK(write(fd,&nbr, 8));

    //fermeture fichier
    CHK(close(fd));

}