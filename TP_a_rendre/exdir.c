/**
 * @brief Fichier exdir.c
 * 
 */
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fnmatch.h>

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


int exdir(const char * chemin){
    DIR * dir;
    struct dirent *dp;
    dir=opendir(chemin);
    if(!dir){
        perror(chemin);
        return 0;
    }
    if( (dp=readdir(dir)) == NULL){
        perror("Repertoire vide");
        return 0;
    }

    while((dp=readdir(dir))!= NULL){
        if((strcmp(dp->d_name, ".") == 0) ||
        (strcmp(dp->d_name, "..") == 0) ||
        (fnmatch(".*",dp ->d_name,0)==0)){
            continue;
        }
        // creation nouvelle chaine pour aller dans le sous-repertoire
        char subpath[PATH_MAX];
        //concatenation path de debut et chemin courant
        if((snprintf(subpath,sizeof(subpath),"%s/%s",chemin,dp->d_name) ) > PATH_MAX){
            raler("Taille depassee");
        }
        struct stat st_buf;
        // recuperation des donnees du repertoire
        if(stat(subpath,&st_buf) == -1){
            raler("Stat");
        }

    }
    return 0;
}

/**
 * @brief Fichier main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[]){
    //tester nombre d'arguments passees en parametres
    if(argc != 2){
        fprintf(stderr, "Erreur us : %s <source> \n",argv[0]);
        exit(EXIT_FAILURE);
    }

    //creation de repertoire recevant les fichiers resultats 
    char Resultat[PATH_MAX];
    sprintf(Resultat, "/tmp/%d", getuid());
    
    if(mkdir(TMP_repertoire,07000)==-1){
        raler("Creation repertoire\n");
    }

    exdir(argv[1]);

    
    return 0;
}
// Modalités de rendu : 
// - dépôt sur Moodle (dans le dépôt qui concerne votre groupe)
// - commit et push sur votre dépôt git

// # Date limite de rendu : 
// - lundi 13 mars 17h00

 
