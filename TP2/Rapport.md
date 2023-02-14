# Exercice 1

# Question 1 
# Dans quel fichier man peut-on trouver la description de la structure struct stat ?
    
    La structure stat se trouve dans le fichier "man stat(1)".
    Il faut inclure les fichiers d'en-tete:
        #include <sys/types.h>
        #include <sys/stat.h>
        #include <unistd.h>

# Question 2
# Quel attribut de la structure stat stocke les permissions du fichier et quelle opération effectuer afin de récuperer uniquement cette information ?

    L'attribut qui contient les permissions du fichier est le st_mode. Il faut y appliquer un masque via les macros S_IRWXU|S_IRWXG|S_IRWXO afin de recuperer ces permissions.

# Question 3
#  Comment interpréter les permissions à partir de la représentation en base octale ?

    Les permissions sont renvoyes sur la base de 3 chiffres en octal:
        le premier octal contient les permissions de l'utilisateur,le deuxieme celles du groupe,le dernier celles des autres.
        7 : acces en lecture/ecriture/execution
        6 : acces en lecture/ecriture
        5 : acces en ecriture/execution
        4 : acces en lecture
        3 : acces lecture/ecriture
        2 : acces ecriture
        1 : acces execution

# Question 4
# Quelles sont les macros POSIX pour vérifier le type de fichier (dans le champ st_mode) ?

Les macros POSIX qui le permettent sont:
    S_ISREG(m)
    S_ISDIR(m)
    S_ISCHR(m)
    S_ISBLK(m)
    S_ISFIFO(m)
    S_ISLNK(m)
    S_ISSOCK(m)



# Exercice 2
