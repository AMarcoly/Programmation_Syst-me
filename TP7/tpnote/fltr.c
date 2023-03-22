
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
/* vous n'avez normalement pas besoin de plus */

/* gestion des erreurs */
void raler (const char * msg)
{
    perror (msg);
    exit (EXIT_FAILURE);
}
#define CHK(op) do { if ((op) == -1) raler (#op); } while (0)


int main (int argc, char * argv [])
{
    if (argc != 4)
    {
        fprintf (stderr, "Usage: %s entree rebut sortie\n", argv[0]);
        exit (EXIT_FAILURE);
    }
    /*
      argv[1] : nom du fichier entree
      argv[2] : nom du fichier rebut
      argv[3] : nom du fichier sortie
    */

    /* à vous d'écrire le reste */

    // declaration des tubes
    int tube12[2];
    int tube23[2];
    //declaration des pid
    pid_t pid_fils1,pid_fils2,pid_fils3;
    //declaration des file_descriptor
    int entree,sortie,rebut;
    //taille lue par buff
    ssize_t n;
    //stockage lecture
    char buff[8];
    // renvoie raison
    int raison1,raison2,raison3;

    // creation tube
    CHK(pipe(tube12));

    CHK(pid_fils1=fork());

    switch(pid_fils1){
    case -1: raler("fork");
        break;
    case 0: 
        CHK(close(tube12[0]));
        CHK(entree=open(argv[1],O_RDONLY));

        CHK(dup2(entree, STDIN_FILENO));
        CHK(dup2(tube12[1],STDOUT_FILENO));

        CHK(close(entree));
        CHK(close(tube12[1]));

        CHK(execlp("tr","tr",".#","01",NULL));
        //exit(0);
    }

    CHK(pipe(tube23));

    CHK(pid_fils2=fork());

    switch (pid_fils2){
        case -1 :
            raler("fork");
            break;
        case 0: 
            CHK(close(tube12[1]));
            CHK(close(tube23[0]));
            CHK(rebut = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666));
            //lecture dans le pipe directement et mis dans buff
           while((n=read(tube12[0],buff,8))!=0){
                if(n>= 1 && n<8){
                    printf("Lecture impossible\n");
                    exit(EXIT_FAILURE);
                }
                else if(buff[0] == buff[6]){
                //pas de O_create
                    CHK(write(rebut,buff,8));
                }else {
                    CHK(write(tube23[1],buff,8));
                }
            }
            if(n==-1)
                raler("read");

           CHK(close(tube12[0]));
           CHK(close(tube23[1]));
           CHK(close(rebut));
            exit(0);      
    }

    CHK(pid_fils3=fork());

    switch(pid_fils3){
        case -1: raler("fork");
            break;
        case 0 : 
            CHK(close(tube12[0]));
            CHK(close(tube12[1]));
            CHK(close(tube23[1]));
            CHK(sortie = open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,0666));
            

            //dup 
            CHK(dup2(tube23[0],STDIN_FILENO));
            CHK(dup2(sortie,STDOUT_FILENO));
            

            //close
            CHK(close(tube23[0]));
            CHK(close(sortie));

            if(execlp("cat","cat","-n",NULL) == -1) raler("execlp");
            //exit(0);
    }


    //pere
    CHK(close(tube12[0]));
    CHK(close(tube12[1]));
    CHK(close(tube23[0]));
    CHK(close(tube23[1]));

    // les close avant les wait
    waitpid(pid_fils1,&raison1,0);
    waitpid(pid_fils2,&raison2,0);
    waitpid(pid_fils3,&raison3,0);
   
    if((raison1==0) && (raison2==0) && (raison3==0)){
        exit(EXIT_SUCCESS);
    }

    else if(WIFSIGNALED(raison1) || WIFSIGNALED(raison2) || WIFSIGNALED(raison3)) exit(2);

    exit(EXIT_FAILURE);
}
