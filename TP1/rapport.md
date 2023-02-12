# Rapport

# Exo1

# Question 1

Les flags se trouvent dans la page 2 du man de open. Commande "man 2 open".
Il faut donc mettre les fichiers includes : 
    <sys/types.h>
    <sys/stat.h>
    <fcntl.h>



# Question 2

Les informations sur les contantes sur la page du man open. Commande "man 2 open"
Il faut inclure en en-tete :
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
# Question 3

Si on oublie de mettre le flag O_CREAT on a le message d'erreur :
    dest=open(fichierdest,O_WRONLY )
    No such file or directory

Ce message nous dit que la primitive systeme open a echoue car elle n'a pas pu ouvrir le fichier destination qui n'existe pas.

# Question 4
Si on oublie de mettre les permissions le fichier est cree mais on n'arrivera pas l'ouvrir, par exemple si on effectue dessus la commande cmp on aura le message d'erreur;

cmp test1.odt test2.odt 
cmp: test2.odt: Permission non accordée

le fichier sera donc protege.
# Exercice 2

# Question 1
    Les informations sur fopen se trouve sur dans le man avec la commande "man fopen".
    Il faut inclure l'en-tete: 
        #include <stdio.h>

# Question 2
    Si le fichier n'existe pas il est cree automatiquement.
# Question 3
    La constante EOF 

# Exercice 3
Le temps d'exec avec cp_sys est :

time ./cp_sys ../bigfile ../bigfile2

real	3m29,042s
user	0m8,784s
sys	3m20,220s


Avec cp-std le temps d'execution est ;
    time ./cp_std ../bigfile ../bigfile2

real	0m0,527s
user	0m0,435s
sys	0m0,092s


La fonction cd_std est beaucoup plus efficace que la fonction cp_sys

| Temps `cp_std` (ms) |
    |:----------------:|
    | 504(ms)|

    |Taille du buffer (octets) | Temps `cp_sys` (ms) |
    |:----------------:|:--------------:|
    |  1               |   17293        |
    |  8               | 8981           |
    |  16              |649             |
    |  256             | 347            |
    |  512             |  216           |
    |  1024            |  144           |
    |  4096            |  104           |

# exercice 5

# Question 1 Que se passe-t-il si on essaie de lire à une position de valeur négative ?

La fonction lseek nous renvoie l'erreur :
    lseek(fd_fichier,pos,SEEK_SET)
    Invalid argument
car la position negative est un argument invalide et empeche donc le placement du curseur.

# Question 2 Que se passe-t-il si on essaie de lire au delà de la fin du fichier ?

    Le programme renvoie l'entier 0 ceci est du au fait qu'il n'y a pas de valeur a cet endroit donc
    pour puvoir fonctionner il remplit jusqu'a position avec des zeros. Ceci nous empeche de voir s'il y a erreur ou pas.
        "L'entier lu est 0"

# Question 3 Comment faire pour afficher une erreur dans ce cas ?

Pour pallier a ceci j'ai mis une condition pour que la position doit obligatoirement etre un nombre entre 0 et taille du fichier.
Taille que j'ai recupere via la structure stbuf.