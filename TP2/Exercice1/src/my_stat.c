/**
 * @file my_stat.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/raler.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/sysmacros.h>

void my_stat(char * const fichier_src){
    //Variables
    int file_descriptor;
    struct stat st_buf;
    long mode;

    //ouverture du fichier
    CHK(file_descriptor = open(fichier_src,O_RDONLY, 0666) );

    //recuperation des donnees
    CHK(stat(fichier_src,&st_buf));

    mode = st_buf.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO) ;

    // Affichage des valeurs demandees
    printf("UID : %d\n",st_buf.st_uid);    //affichage user id
    printf("GID : %d\n",st_buf.st_gid);    //affichage groupe id
    printf("File size : %ld octets\n",st_buf.st_size);  //affichage taille du fichier
    if(S_ISREG(st_buf.st_mode)){
        printf("Type : regulier\n");
    }else{
        printf("Type : repertoire\n");
    }            //affichage type de fichier
    printf("Mode : %lo\n",mode);   //affichage en octal mode 

    //fermeture du fichier
    CHK(close(file_descriptor));
}

int main(int argc , char * argv[]){

    if(argc!= 2){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    //appel de fonction
    my_stat(argv[1]);
    exit(EXIT_SUCCESS);
}


