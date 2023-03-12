/**
 * @file cp_rev.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdnoreturn.h>



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


void cp_rev(const char * fichiersrc, const char * fichierdest){
    //declaration des variables
    int fd_src, fd_dest;
    char c;
    ssize_t n; //nombre de caracteres dans le fichier


    //ouverture des fichiers
    CHK( fd_src=open(fichiersrc,O_RDONLY));
    CHK(fd_dest=open(fichierdest, O_WRONLY | O_CREAT | O_TRUNC, 0666));



    //positionnement en derniere position du curseur
    CHK(n=lseek(fd_src, -1,SEEK_END )); //n contient le nombre de bytes du fichier

    //boucle de copie
    while ( n >= 0 ) {
        CHK(read(fd_src,&c,1));
        //printf("%c\n",c);
        CHK(write(fd_dest,&c,1));
        if(n!=0)
            CHK(lseek(fd_src, -2, SEEK_CUR));
        n--;//decrementation du nombre d'octets 
    }



    // //recuperation nombre d'octets
    // CHK(stat(fichiersrc,&stbuf));
    // size=stbuf.st_size;

    // //positionnement en derniere position du curseur
    // CHK(size=lseek(fd_src,-1,SEEK_END)); //n contient le nombre de bytes du fichier
    // //lseek renvoie taille du fichier
    // size--;
    // CHK(lseek(fd_src,size,SEEK_CUR));
    // CHK(read(fd_src,&c,1));
    // printf("%c\n",c);

    //boucle de copie
    // while ( size >= 0 ) {
        
    //     CHK(lseek(fd_src,size,SEEK_CUR));
    //     CHK(read(fd_src,&c,1));
    //     printf("%c\n",c);
    //     CHK(write(fd_dest,&c,1));
    //     size-=2;

    //     // if(n!=0)
    //     //     CHK(lseek(fd_src, -2, SEEK_CUR));
    //     // n--;//decrementation du nombre d'octets 
    // }

    CHK(close(fd_src));
    CHK(close(fd_dest));
}

int main(int argc,  char * argv[]){

     //test du nombre d'arguments
    if( argc != 3){
        fprintf(stderr, "Erreur us : %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    //Appel fonction
    cp_rev(argv[1],argv[2]);
    
    exit(EXIT_SUCCESS);
}