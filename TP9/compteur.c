#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define CHK(op) do { if ( (op) == -1) raler (#op);  } while(0)

/**
 * @brief Fonction raler qui va s'occuper d'afficher les erreurs sur la sortie erreur standard
 * 
 * @param msg 
 */

void raler(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

volatile sig_atomic_t compteur=0; 

void f(int sig){
	(void)sig;
	compteur++;
	char msg[256];
	snprintf(msg,256,"\t compteur : %d\n",compteur);
	if((write(1,msg,strlen(msg))) == -1)
		raler("write");
}

int main(){
	struct sigaction s;
	s.sa_handler =f; 
	s.sa_flags=0; 
	sigemptyset(&s.sa_mask);
	if(sigaction(SIGINT,&s,NULL)==-1){
		raler("sigaction");
	}

	sigset_t vide,mask,old;
	sigemptyset(&vide); 

	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);

	sigprocmask(SIG_BLOCK,&mask,&old);

	// debut section critique
	while(compteur<5){
		sigsuspend(&vide);
		// printf("Compteur =%d\n",compteur);
	}
	//fin section critique
	if(sigprocmask(SIG_SETMASK,&old,NULL)==-1) raler("sigpromask");
}
// on evite de mettre printf dans les fonctions traitantes, mais tp demande c pas grave.
// mieux vaut use write dans fonction traitante.
