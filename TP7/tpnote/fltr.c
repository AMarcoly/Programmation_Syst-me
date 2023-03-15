
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
#define CHECK(op) do { if ((op) == -1) raler (#op); } while (0)


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


}
