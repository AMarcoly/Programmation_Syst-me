/**
 * @file cp_std.c
 * @author Marcoly ANTOINE (marcoly.antoine@etu.unistra.fr)
 * @brief Main de l'exercice 2
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #include "../include/raler.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Fonction qui prend en parametre deux noms de fichiers
 et copie les donnees du fichier source dans le fichier destination
 * 
 * @param fichiersrc 
 * @param fichierdest 
 */
 void cp_std (const char *fichiersrc, const char *fichierdest){
    FILE *src, *dest; //
    int c;//entier qui va prendre le retour de fget 

    //ouverture du fichier source
    CHK(src=fopen(fichiersrc, "r"));
    //ouverture du fichier destination
    CHK(dest=fopen(fichierdest,"w"));

    //boucle de la copie
    while ((c = fgetc(src)) != EOF )
        if (fputc(c,dest) == EOF )   //si on arrive a la fin de notre fichier
            raler(1,"putc");
    
    //test si message d'erreur
    if ( ferror(src))
        raler(1,"getc");

    CHK2(fclose(src));//fermeture fichier source
    CHK2(fclose(dest));//fermeture fichier destination

    exit(EXIT_FAILURE);
}

/**
 * @brief main pour faire les test
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char * argv[]){

    //test si bon nombre d'arguments
    if(argc != 3){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //appel de la fonction
    cp_std(argv[1],argv[2]);

    exit(EXIT_SUCCESS);
}