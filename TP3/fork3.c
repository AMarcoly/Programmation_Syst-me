#include <stdio.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>
#include <fcntl.h>

#define CHK(op) do { if ( (op) == -1) raler (#op);  } while(0)


void raler(const char * msg){
	perror(msg);
	exit(1);
}

/*
Écrire le programme fork3  qui prend un nom de fichier en paramètre et qui :
ouvre le fichier en lecture;
créé un processus fils;
puis les deux processus (père et fils) lisent les caractères l’un après l’autre dans le fichier en utilisant la primitive système read, 
et les écrivent avec write sur la sortie standard.
Expérimentez ce programme avec un fichier texte de taille assez grande.
*/
void fork3(const char * pathname){
	// variables
	int file_descriptor;
	pid_t pid_fils;
	ssize_t nbr_octets;
	int status;
	char c;
	int file_d_sortie;
	int caractere_lu=0;

	// ouverture du fichier en lecture
	CHK(file_descriptor= open(pathname,O_RDONLY));
	CHK(file_d_sortie = open("sortie.txt",O_WRONLY|O_CREAT|O_TRUNC,0666));

	// Question 1 redirection vers fichier
	dup2(file_d_sortie,STDOUT_FILENO);
	CHK(close(file_d_sortie));

	// creation du processus fils
	CHK(pid_fils = fork());

	// switch
	switch (pid_fils){
		case -1 :
			raler("fork");
		case 0 : // fils 
			while((nbr_octets=read(file_descriptor,&c,1))>0){
				CHK(write(STDOUT_FILENO,&c,1));
				caractere_lu += nbr_octets;
			}
			if(nbr_octets==-1) raler("read");
			exit(EXIT_SUCCESS);
	}

	// pere 
	CHK(wait(&status));
	if (WIFEXITED(status)){

		while((nbr_octets=read(file_descriptor,&c,1))>0){
				CHK(write(STDOUT_FILENO,&c,1));
				caractere_lu += nbr_octets;
		}
		CHK(nbr_octets);
		CHK(close(file_descriptor));
	}
	else{
		CHK(close(file_descriptor));
		raler("echec sortie");
	}
}


int main(int argc, char * argv[]){
	//test si bon nombre d'arguments
    if(argc != 2){
        fprintf(stderr, "Erreur us : %s <source> > \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //appel de la fonction
    fork3(argv[1]);

    exit(EXIT_SUCCESS);

}


// version 1 

// void fork3(const char * pathname){
// 	// variables
// 	int file_descriptor;
// 	pid_t pid_fils;
// 	ssize_t nbr_octets;
// 	int status;
// 	char c;
// 	int caractere_lu=0;

// 	// ouverture du fichier en lecture
// 	CHK(file_descriptor= open(pathname,O_RDONLY));

// 	// creation du processus fils
// 	CHK(pid_fils = fork());

// 	// switch
// 	switch (pid_fils){
// 		case -1 :
// 			raler("fork");
// 		case 0 : // fils 
// 			while((nbr_octets=read(file_descriptor,&c,1))>0){
// 				CHK(write(STDOUT_FILENO,&c,1));
// 				caractere_lu += nbr_octets;
// 			}
// 			if(nbr_octets==-1) raler("read");
// 			exit(EXIT_SUCCESS);
// 	}

// 	// pere 
// 	CHK(wait(&status));
// 	CHK(close(file_descriptor));
// 	exit(EXIT_SUCCESS);
// }
