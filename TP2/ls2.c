#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fnmatch.h>
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

//fonction pour afficher les differentes modes du fichier
void permission(mode_t mode){
	printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\t");
}

void ls2(void){
	//variables
	DIR *dir;
	struct dirent *d;
	struct stat st_buf;


	//ouverture repertoire
	dir=opendir(".");
	if(dir==NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }

	//parcours du repertoire
	while((d=readdir(dir))!=NULL){
		if((strcmp(d->d_name,".")!= 0) && 	// on reste dans le repertoire courant
			fnmatch(".*",d->d_name,0)!=0) {	// ne commence pas par un point
			CHK(stat((d->d_name),&st_buf)); // recuperation des données
			permission(st_buf.st_mode);		//affichage des permissions
			printf("%s \n",d->d_name);		//affichage du nom
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
    if(argc < 1){
        fprintf(stderr, "Erreur us : %s <source> \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //appel de la fonction
    ls2();

    exit(EXIT_SUCCESS);
}