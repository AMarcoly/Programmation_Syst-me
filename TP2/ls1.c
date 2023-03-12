#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fnmatch.h>


#define CHK(op) do { if ( (op) == -1) raler (1,#op);  } while(0)
#define CHK2(op) do { if ( (op) == NULL) raler (1,#op);  } while(0)

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

void ls1(void){
	//variables
	DIR * dir;		// pointeur sur ouverture repertoire c comme le file_descriptor pour les fichiers
	struct dirent *d;	//structure recevant les informations dans le repertoire


	//ouverture repertoire
	CHK2(dir=opendir("."));

	//parcours du repertoire
	while((d=readdir(dir))!=NULL){
		if((strcmp(d->d_name,".")!= 0) && 
			//(strcmp(d->d_name,"..")!= 0) &&
			fnmatch(".*",d->d_name,0)!=0) {
			printf("%s \n",d->d_name);
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
    ls1();

    exit(EXIT_SUCCESS);
}