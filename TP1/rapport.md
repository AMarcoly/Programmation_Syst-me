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


# Question 2

# Question 3


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