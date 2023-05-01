#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

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


void read_int(const char * filename, off_t pos, int64_t number){
	//declaration variables
	ssize_t size = 0;
	int fd =0;
	int zero = 0;

	//ouverture fichier source
	CHK(fd=open(filename,O_WRONLY|O_CREAT,0666));
	//recuperation de la taille du fichier
	CHK(size=lseek(fd,0,SEEK_END));

	//test si pos>size on remplit avec des zeros
	if( (pos > size)){
		for (int i = size; i<pos ; i++){
			CHK(write(fd,&zero,1));
		}
	}

	// Si la position donnee est negative	
	if(pos<0){
		perror("Position invalide\n");
		exit(1);
	}

	//On se deplace jusqu'a la position
	lseek(fd,pos,SEEK_SET);

	//on ecrit un int_64 pour la taille on use size of
	CHK(write(fd,&number,sizeof(number)));

	//fermeture fichier source
	CHK(close(fd));

}


int main(int argc,  char * argv[]){

     //test du nombre d'arguments
    if( argc != 4){
        fprintf(stderr, "Erreur us : %s <source> <pos> <int64t>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    //Appel fonction
    read_int(argv[1],atoi(argv[2]),atoi(argv[3]));
    
    exit(EXIT_SUCCESS);
}