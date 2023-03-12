#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

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


void read_int(const char * filename, int pos){
	//declaration variables
	ssize_t size = 0;
	int fd =0;
	int64_t buf;

	//ouverture fichier source
	CHK(fd=open(filename,O_RDONLY));
	//recuperation de la taille du fichier
	CHK(size=lseek(fd,0,SEEK_END));

	//test si 0<=pos<size 
	if((0 > pos) || (pos >= size))
		raler(1,"Erreur position inexistante");

	//On se deplace jusqu'a la position
	CHK(lseek(fd,pos,SEEK_SET));

	//on lit un int_64 pour la taille on use size of
	CHK(read(fd,&buf,sizeof(int64_t)));
	printf("%lld\n",(int64_t)buf );

	//fermeture fichier source
	CHK(close(fd));

}


int main(int argc,  char * argv[]){

     //test du nombre d'arguments
    if( argc != 3){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    //Appel fonction
    read_int(argv[1],atoi(argv[2]));
    
    exit(EXIT_SUCCESS);
}