# Rapport

# Exo1

1. Les flags se trouvent dans la page 2 du man de open. Commande "man 2 open".
Il faut donc mettre les fichiers includes : 
    <sys/types.h>
    <sys/stat.h>
    <fcntl.h>

2. Les informations sur les constantes sur la page du man open. Commande "man 2 open"
Il faut inclure en en-tete :
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

3. Si on oublie de mettre le flag O_CREAT on a le message d'erreur :
    dest=open(fichierdest,O_WRONLY )
    No such file or directory
    
    Ce message nous dit que la primitive systeme open a echoue car elle n'a pas pu ouvrir le fichier destination qui n'existe pas.(car n'a pas ete cree).

4. Si on oublie de mettre les permissions le fichier est cree mais on n'arrivera pas l'ouvrir, par exemple si on effectue dessus la commande cmp on aura le message d'erreur;

    cmp test1.odt test2.odt 
    cmp: test2.odt: Permission non accordée

    Le fichier sera donc protege.
    Cela est du notamment au fait que le fichier a recupere le premier nombre qu'il a trouve sur la pile comme permission, ce nombre est aleatoire.

## Exercice 2


1. Les informations sur fopen se trouve sur dans le man avec la commande "man fopen".
    Il faut inclure l'en-tete: 
        #include <stdio.h>

2. Si le fichier n'existe pas il est cree automatiquement.

3. La constante EOF est un caractere utilise pour notifier de la fin d'un fichier. Ce n'est pas un caractere present dans le fichier.

# Exercice 3

1. Le temps d'exec avec cp_sys est :

    time ./cp_sys ../bigfile ../bigfile2

    real	3m29,042s
    user	0m8,784s
    sys	3m20,220s

2. Avec cp-std le temps d'execution est ;
    time ./cp_std ../bigfile ../bigfile2

    real	0m0,527s
    user	0m0,435s
    sys	0m0,092s


- La fonction cd_std est beaucoup plus efficace que la fonction cp_sys

| Temps `cp_std` (ms)|
|:----------------:|
| 504(ms)|


| Taille du buffer(octets) | Temps cp_sys (ms) |
|:------------------------:|:-----------------:|
|            1             |      17 293       | 
|            8             |      8 981        | 
|            16            |       649         | 
|           256            |       347         |
|           512            |       216         |
|           1024           |       144         |
|           2048           |        104        |

2. La taille de buffer utilise est d'au moins 512 octets dans les bibliotheques standard.(Généralement on utilise 1 024 octets).

# Exercice 4

1. Comment positionner la tête de lecture à la fin du fichier ?
    Pour positionner la tete de lecture a la fin du fichier on utilise la fonction lseek avec comme option SEEK_END.

2. Comment faire « reculer » la tête de lecture ?
    TOn recule la tete de lecture toujours en utilisant lseek. Mais en utilisant SEEK_CUR et une position relative en negatif.
    Cependant on doit faire attention a au plus revenir a la position 0.
3. Quelles sont les différentes possibilités pour connaître la taille d'un fichier ?
    Il esxiste differentes possibilites :
        - stat()
        - en utilisant lseek(comme fait dans cp_rev)
        
# Exercice 5

1.  Que se passe-t-il si on essaie de lire à une position de valeur négative ?

    La fonction lseek nous renvoie l'erreur :
    lseek(fd_fichier,pos,SEEK_SET)
    Invalid argument
    car la position negative est un argument invalide et empeche donc le placement du curseur.

2. Que se passe-t-il si on essaie de lire au delà de la fin du fichier ?

    Le programme renvoie l'entier 0 ceci est du au fait qu'il n'y a pas de valeur a cet endroit donc
    pour puvoir fonctionner il remplit jusqu'a position avec des zeros. Ceci nous empeche de voir s'il y a erreur ou pas.
        "L'entier lu est 0"

3.  Comment faire pour afficher une erreur dans ce cas ?

    Pour pallier a ceci j'ai mis une condition pour que la position doit obligatoirement etre un nombre entre 0 et taille du fichier.

4. Si on écrit au delà de la fin du fichier. Des zeros sont ajoutés jusqu'à la position où l'on souhaite écrire.