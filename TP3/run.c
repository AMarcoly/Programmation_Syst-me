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

void raler(const char * msg){
	perror(msg);
	exit(1);
}

/**
 * Écrire le programme run qui prend en paramètre un nom de commande Unix suivi de ses paramètres, puis crée un processus fils
 *  qui exécute cette commande à l'aide de execvp.
 * Le processus père attend la terminaison de son fils puis affiche le code de retour du fils. 
 * Si la commande Unix donnée en paramètre n'est pas une commande valide, le processus fils retourne le code 2.
*/
int main(int argc, char * argv[]){

	//variables
	pid_t pid; 
	int status;

	// declaration tableau de string 
	char * tab[argc];

	// recuperation des arguments de la commande Unix place en parametre
	for(int i=0; i<argc-1; i++){
		char * tmp = argv[i+1];	
		tab[i]= (char *)tmp;
	}
	tab[argc-1]=NULL;

	// fork
	CHK(pid=fork());

	switch(pid){
		case -1 : raler("fork");
			break; 
		case 0 : //fils 
			if( execvp(tab[0],tab)  == -1 ){
				perror("execvp");
				exit(2);	
			}
	}

	//attendre que le fils se termine
	if(waitpid(pid,&status,0)== -1 ) raler("waitpid");

	// affichage code de retour fils
	if(WIFEXITED(status))
		printf("Le code de retour du fils est : %d\n",WEXITSTATUS(status));

	exit(EXIT_SUCCESS);
}
