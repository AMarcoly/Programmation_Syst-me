#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <fnmatch.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define CHK(op) do { if ( (op) == -1) raler (1,#op);  } while(0)

noreturn void raler(int syserr,  const char *msg, ...){
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr,msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    if(syserr == 1)
        perror("");

    exit(EXIT_FAILURE);
}


void ls_rec(char * pathname){
    DIR * dir;
    struct dirent *dp;
    
    //ouverture du repertoire
    dir=opendir(pathname);
    if(dir==NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    //boucle d'affichage
    while((dp=readdir(dir))!=NULL){
        //test si repertoire vide , on continue
        if(strcmp(dp->d_name,".")==0 ||
            strcmp(dp->d_name,"..")==0 ||
            fnmatch(".*",dp ->d_name,0)==0){
            continue; 
        }

        // creation nouvelle chaine pour aller dans le sous-repertoire
        char subpath[PATH_MAX];
        //concatenation path de debut et chemin courant
        snprintf(subpath,sizeof(subpath),"%s/%s",pathname,dp->d_name);
        struct stat st_buf;
        // recuperation des donnees du repertoire
        CHK(stat(subpath,&st_buf));
        //affichage du chemin
        printf("%s",subpath);

        //tester si repertoire et appeler recursivement
        if(S_ISDIR(st_buf.st_mode)){
            printf("/ \n");
            ls_rec(subpath);
        }
        else{
            printf("\n");
        }
    }

    //fermeture du repertoire
    CHK(closedir(dir));
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
    if(argc != 2){
        fprintf(stderr, "Erreur us : %s <source> \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //appel de la fonction
    ls_rec(argv[1]);

    exit(EXIT_SUCCESS);
}


