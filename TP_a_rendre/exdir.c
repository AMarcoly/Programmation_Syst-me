/**
 * @brief Fichier exdir.c
 * 
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define TMP_repertoire "/tmp"

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
 * @brief Fonction qui verifie si le fichier est executable par utilisateur courant.
 * 
 * @param chemin 
 * @return int 
 */
int est_executable(const char * chemin){
    //recuperation des donnees
    struct stat st_buf;
    if(stat(chemin,&st_buf)== -1){
       raler("Executable");
    }
    return st_buf.st_mode & S_IXUSR;
}

/**
 * @brief Fonction verifiant l'accessibilite du fichier pour l'user courant (existence et exec)
 * 
 * @param chemin 
 * @return int 
 */
int est_accessible(const char * chemin){
    if(!(access(chemin, F_OK|X_OK))){
        raler("Accessibilite");    
    }
    return 1;
}

/**
 * @brief Fonction verifiant si le fichier passer en parametre est bien un repertoire
 * 
 * @param chemin 
 * @return int 
 */
int est_un_repertoire(const char * chemin){
    struct stat st_buf;
    if(stat(chemin,&st_buf)==-1){
        raler("repertoire");
    }
    return S_ISDIR(st_buf.st_mode);
}

/**
 * @brief Fichier main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[]){
    if(argc != 2){
        fprintf(stderr, "Erreur us : %s <source> \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Bonjour\n");
    return(1);
}
// Modalités de rendu : 
// - dépôt sur Moodle (dans le dépôt qui concerne votre groupe)
// - commit et push sur votre dépôt git

// # Date limite de rendu : 
// - lundi 13 mars 17h00

 
