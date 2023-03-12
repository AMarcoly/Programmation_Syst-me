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



/**
 * @brief Fonction raler qui va s'occuper d'afficher les erreurs sur la sortie erreur standard
 * 
 * @param msg 
 */
void raler(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void exdir(const char * chemin){
    
    DIR * dir;
    struct dirent *dp;

    if((dir=opendir(chemin) )== NULL){
        raler("Erreur opendir");
    }
    
    //creation de repertoire recevant les fichiers resultats 
    char Resultat[PATH_MAX];
    sprintf(Resultat, "/tmp/%d", getuid());
    
    if(access(Resultat,F_OK)==-1){
        if(mkdir(Resultat,S_IRWXU) ==-1){
        raler("Erreur sur creation Creation repertoire\n");
    }
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
        snprintf(subpath,sizeof(subpath),"%s/%s",chemin,dp->d_name);
        if(strlen(subpath)>=PATH_MAX){exit(1);}

        if(dp->d_type == DT_DIR){
            if(access(subpath,R_OK|X_OK)== -1){
                continue;    
            }
            exdir(subpath);
        }else if(dp->d_type== DT_REG){
            //cas fichier regulier
            if(access(subpath,R_OK|X_OK)== 0){
                //
                char * fichier_de_sortie = malloc(PATH_MAX+strlen(dp->d_name) + 3);
                if(fichier_de_sortie==NULL){
                    raler("Erreur Malloc");
                }  

                snprintf(fichier_de_sortie, PATH_MAX + strlen(dp->d_name) + 2, "/tmp/%d/%s", getuid(), dp->d_name);
                if(strlen(fichier_de_sortie)>=PATH_MAX){exit(1);}
                
                int fd = open(fichier_de_sortie,O_WRONLY|O_CREAT|O_TRUNC,0644);
                if(fd==-1) raler("Erreur sur ouverture fichier de sortie");

                char * args[] = {"file","--mime-type",(char *)subpath,NULL};
                pid_t pid = fork();

                if(pid ==-1){
                    raler("fork");
                }
                if(pid == 0){
                    if(execvp(args[0],args)== -1){raler("execvp");}
                    if(close(fd)==-1){raler("close");}
                    free(fichier_de_sortie);
                    exit(EXIT_SUCCESS);
                }
                else{
                    int status;
                    if(waitpid(pid,&status,0)==-1) raler("waitpid");
                    else if(!WIFEXITED(status) || WEXITSTATUS(status) != 0) raler("waitpid non sortie");
                }
            }
        }  
    }//fin du while
    //fermeture repertoire
    if(closedir(dir) ==-1){
        raler("Fermeture repertoire");
    }
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

 
