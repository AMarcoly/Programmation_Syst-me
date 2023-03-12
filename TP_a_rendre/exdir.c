/**
 * @brief Fichier exdir.c
 * 
 */
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fnmatch.h>

#define TMP_repertoire "/tmp"

/**
 * @brief Fonction raler qui va s'occuper d'afficher les erreurs sur la sortie erreur standard
 * 
 * @param msg 
 */
void raler(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

/**
 * @brief Fonction qui verifie si le fichier est executable par utilisateur courant.
 * 
 * @param chemin 
 * @return int 
 */
int est_executable(const char * chemin){
    //recuperation des donnees
    struct stat st_buf;
    if(stat(chemin,&st_buf)== -1){
       raler("Executable");
    }
    return st_buf.st_mode & S_IXUSR;
}

/**
 * @brief Fonction verifiant l'accessibilite du fichier pour l'user courant (existence et exec)
 * 
 * @param chemin 
 * @return int 
 */
int est_accessible(const char * chemin){
    if(!(access(chemin, F_OK|X_OK))){
        raler("Non accessible");    
    }
    return 1;
}

/**
 * @brief Fonction verifiant si le fichier passer en parametre est bien un repertoire
 * 
 * @param chemin 
 * @return int 
 */
int est_un_repertoire(const char * chemin){
    struct stat st_buf;
    if(stat(chemin,&st_buf)==-1){
        raler("N'est pas un repertoire");
    }
    return S_ISDIR(st_buf.st_mode);
}

int est_un_fichier(const char * chemin){
    struct stat st_buf;
    if (stat(chemin,&st_buf) == -1) {
        raler("Test fichier echoue");
    }
    return S_ISREG(st_buf.st_mode);
}

int gestion_fichier(const char * chemin){
    //tester si fichier executable
    if(!est_executable(chemin)){
        raler("Fichier non executable");
    }

    char sous_chemin[PATH_MAX];
    if((snprintf(sous_chemin, sizeof(sous_chemin),"%s/%d/%s",TMP_repertoire,getuid(),chemin) ) >= PATH_MAX )
    {
        raler("Chemin trop long");
    }

    //ouverture fichier
    int fd = open(sous_chemin,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(fd==-1){
        raler("Erreur ouverture fichier ");
    }

    char * args[] = {"file","--mime-type",(char *)chemin,NULL};
    pid_t pid = fork();
    switch(pid){
        case -1 : 
            perror("Erreur PID");
            exit(EXIT_FAILURE);
        case 0  :
            {
                dup2(fd,STDOUT_FILENO);
                close(fd);
                execvp(args[0],args);
                perror(args[0]);
                exit(EXIT_FAILURE);
            }
        default:{
            int status;
            if(waitpid(pid, &status, 0) == -1){
                raler("Erreur processus pere");
            }

            if(!WIFEXITED(status) || WEXITSTATUS(status) != 0 ){
                fprintf(stderr, "Echec de traitement fichier %s\n",chemin);
            }
            return 1;
        }       

    }
    // return 0;
}


int exdir(const char * chemin){
    
    DIR * dir;
    struct dirent *dp;
    if((dir=opendir(chemin) )== NULL){
        raler("Repertoire inexistant");
    }
    int bit_temoin=1;
     //creation de repertoire recevant les fichiers resultats 
    char Resultat[PATH_MAX];
    sprintf(Resultat, "/tmp/%d", getuid());
    
    if(mkdir(Resultat,0777) ==-1){
        raler("Erreur sur creation Creation repertoire\n");
    }

    while((dp=readdir(dir))!= NULL){
        //test repertoire vide
        if((strcmp(dp->d_name, ".") == 0) ||
        (strcmp(dp->d_name, "..") == 0)){
            continue;
        }
        // creation nouvelle chaine pour aller dans le sous-repertoire
        char subpath[PATH_MAX];
        //concatenation path de debut et chemin courant
        if((snprintf(subpath,sizeof(subpath),"%s/%s",chemin,dp->d_name) ) > PATH_MAX){
            raler("Taille depassee");
        }
        //test si repertoire ou fichier et traitement
        //version 2
         struct stat st_buf;
        // recuperation des donnees du repertoire
        if(stat(subpath,&st_buf) == -1){
            raler("stat");
        }

        if(S_ISDIR(st_buf.st_mode)){
            if(access(subpath,R_OK|X_OK)){
                bit_temoin = bit_temoin & exdir(subpath);
            }
        }
        if(S_ISREG(st_buf.st_mode)){
            if(access(subpath,R_OK|X_OK)){
                bit_temoin = bit_temoin & gestion_fichier(subpath);
            }
        }
        else{
            bit_temoin=0;
        }
        //version 1
       
        // if(est_un_repertoire(subpath)){
        //     if(est_accessible(subpath) && est_executable(subpath)){
        //         bit_temoin = bit_temoin & exdir(subpath);
        //     }
        // }
        // if(est_un_fichier(subpath)){
        //     if(est_accessible(subpath)){
        //         bit_temoin = bit_temoin & gestion_fichier(subpath);
        //     }
        // }
        

        
        
    }//fin du while

    //fermeture repertoire
    if(closedir(dir) ==-1){
        raler("Fermeture repertoire");
    }
    return bit_temoin;
}

/**
 * @brief Fichier main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[]){
    //tester nombre d'arguments passees en parametres
    if(argc != 2){
        fprintf(stderr, "Erreur us : %s <source> \n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if(access(argv[1],X_OK) != 0){
        raler("Repertoire non accessible en execution.");
    }

    exdir(argv[1]);
    return 0;
}
// Modalités de rendu : 
// - dépôt sur Moodle (dans le dépôt qui concerne votre groupe)
// - commit et push sur votre dépôt git

// # Date limite de rendu : 
// - lundi 13 mars 17h00

 
