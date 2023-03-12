#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


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

void my_stat(const char * filename){
	// declaration variables
	int file_descriptor;
	struct stat st_buf;
	long mode;


	//Ouverture du fichier
	CHK(file_descriptor=open(filename,O_RDONLY,0666));

	//recuperation des donnees du fichier
	CHK(stat(filename,&st_buf));
	
	//masque sur mode pour recuperer les droits
	mode = st_buf.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO);

	//ou
	// mode = st_buf.st_mode & S_IRWXU;

	printf("UID : %d\n",st_buf.st_uid);//affichage uid 
	printf("GID : %d\n",st_buf.st_gid); //affichage gid
	printf("File size : %ld\n",st_buf.st_size); //taille du fichier
	if(S_ISREG(st_buf.st_mode)){
		// si c un fichier ordinaire
		printf("Type : regulier\n");
	}
	if(S_ISDIR(st_buf.st_mode)){
		printf("Type : repertoire\n");
	}
	printf("Mode : %lo\n",mode);

	//fermeture du fichier
	CHK(close(file_descriptor));
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
    if(argc < 2){
        fprintf(stderr, "Erreur us : %s <source> \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //appel de la fonction
    my_stat(argv[1]);

    exit(EXIT_SUCCESS);
}