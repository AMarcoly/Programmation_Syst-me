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
#define TAILLE_BUFFER 1024

#include "../include/raler.h"

/**
 * @brief Fonction qui prend en parametres deux noms de fichiers
 * et recopie le contenu du premier dans le second octet par octet
 * @param fichiersrc 
 * @param fichierdest 
 */

void cp_sys(const char * fichier_src, const char * fichier_dest, const int taille_buffer){
    //Declaration des variables
    int fd_src, fd_dest;
    //char caractere_lue;
    //ssize_t n;  // nombre de bits lues

    char buffer[TAILLE_BUFFER];  //octets lus ne pas utiliser char * mais un tableau de taille max buff
    ssize_t n;      //nbr octets lus

    //ouverture des fichiers source et destination
    CHK(fd_src = open (fichier_src,O_RDONLY));
    CHK(fd_dest = open(fichier_dest, O_WRONLY | O_CREAT , 0666));

    //test de la boucle de lecture
    //lecture octet par octet
    //on passe les adresses en parametres

    //version1
    // while( (n = read(fd_src,&caractere_lue,1) ) > 0 ){
    //     CHK(write(fd_dest,&caractere_lue,1));
    // }

   // CHK(n); //test si erreur lecture

    //version_2
    //Faut-il use adresse de buffer ou buffer directement?
    while( (n=read(fd_src,buffer,taille_buffer)) > 0){
        CHK(write(fd_dest,buffer,taille_buffer));
    }

    CHK(n); //test si non erreur lecture

    //fermeture des fichiers
    CHK(fd_src);
    CHK(fd_dest);
}


int main(const int argc , char * argv[]){

     //test du nombre d'arguments
    if( argc != 3){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    //Appel fonction
    cp_sys(argv[1], argv[2],TAILLE_BUFFER);
    
    exit(EXIT_SUCCESS);

}

// void cp_sys(const char *fichiersrc, const char *fichierdest, ){
//     int src,dest;   //va recuperer les fd des fonctions open
//     ssize_t n; 
//     char c; //caractere lire octet par octet

//     //ouverture en lecture seule du premier fichier
//     CHK( src = open(fichiersrc,O_RDONLY));

//     //ouverture en ecriture seule, si le fichier n'existe pas on va le creer avec droits 0666
//     CHK(dest=open(fichierdest,O_WRONLY | O_CREAT , 0666));

//     //boucle de lecture octet par octet
//     while( (n = read(src,&c,1)) > 0 )
//         if ( write (dest,&c,1) == -1) //verifier si prob a l'ecriture
//             raler(1,"write");
//     //si prob a la lecture
//     if(n == -1)
//         raler(1,"read");

//     CHK(close(src)); //fermeture du fichier source
//     CHK(close(dest)); //fermeture du fichier destination
// }

// int main(int argc, char * argv[]){

//     //test du nombre d'arguments
//     if( argc != 3){
//         fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
//         exit(EXIT_FAILURE);
//     }
    
//     //Appel de la fonction copie
//     cp_sys(argv[1],argv[2]);
//     return 0;
// }