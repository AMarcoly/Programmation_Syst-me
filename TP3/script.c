#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>                                                         
#include <sys/uio.h>        
#include <sys/stat.h>  
#include <sys/wait.h>                    


#define CHK(op) do { if ( (op) == -1) raler (#op);  } while(0)
#define CHK2(op) do { if ( (op) == NULL) raler (#op);  } while(0)


void raler(const char * msg){
	perror(msg);
	exit(1);
}


/**
 * Écrivez un programme script.c équivalent au script shell suivant, 
 * qui prend en argument un nom d’utilisateur :
 * ps eaux > toto ; grep "^$1 " < toto > /dev/null && echo "$1 est connecté"
 * Votre programme devra :
 * réaliser effectivement les exécutions de ps et grep 
 * en utilisant la primitive execlp ;
 * mettre en place les redirections des entrées/sorties 
 * nécessaires grâce à la primitive dup (ou dup2) ;
 * réaliser l’affichage final avec la primitive write.
*/

void script(const char * username){
	// variables
	pid_t pid1,pid2,pid3;
	int status1, status2,status3;
	int fd;
	int fd_null;

	CHK(fd = open("toto",O_WRONLY|O_CREAT|O_TRUNC,0666));
	// fork 
	CHK(pid1=fork());

	switch(pid1){
		case -1 : raler("fork");
			break; 
		case 0 : //fils 1 // redirection ps eaux > toto
			CHK(dup2(fd,STDOUT_FILENO));
			CHK(close(fd));
			CHK(execlp("ps","ps","eaux",NULL));
		}

	// pere
	CHK(waitpid(pid1,&status1,0)); // attendre fils 1 se termine

	CHK(pid2=fork());

	switch(pid2){
		case -1 : raler("fork");
			break;
		case 0 : // fils 2 grep "username" < toto > /dev/null i-e on redirige entree standard vers toto et sortie standard vers /dev/null
			
			CHK(fd=open("toto",O_RDONLY));
			CHK(fd_null=open("/dev/null",O_WRONLY,0666));

			// redirections
			CHK(dup2(fd,STDIN_FILENO)); // toto redirige vers entree standard 0
			CHK(dup2(fd_null,STDOUT_FILENO)); // sortie standard redirige vers /dev/null

			//fermer les fichiers
			CHK(close(fd));
			CHK(close(fd_null));

			// executer 
			CHK(execlp("grep","grep",username,NULL));
	}
	
	// attendre cette execution et si reussit alors echo
	CHK(waitpid(pid2,&status2,0));

	if(WIFEXITED(status2) && WEXITSTATUS(status2) == 0){
		CHK(pid3=fork());
		switch (pid3){
			case -1: // erreur
				raler("fork");
			case 0: //fils 
				execlp("echo","echo",strcat((char *)username, " est connecté"),NULL);
		}//fin switch

		CHK(waitpid(pid3,&status3,0));
	}

}




int main(int argc, char * argv[]){
	//test si bon nombre d'arguments
    if(argc != 2){
        fprintf(stderr, "Erreur us : %s <source> <nom_user> \n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //appel de la fonction
    script(argv[1]);

    exit(EXIT_SUCCESS);

}