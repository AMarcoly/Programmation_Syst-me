## Exercice 1
1. La structure stat se trouve dans le fichier "man stat(1)".
    Il faut inclure les fichiers d'en-tete:
        #include <sys/types.h>
        #include <sys/stat.h>
        #include <unistd.h>


2. L'attribut qui stocke les permissions est le st_mode . On peut le récupérer via les opérations bit à bit avec (S_IRWXU|S_IRWXG|S_IRWXO) et la valeur st_mode dans la structure stat.

3. Les permissions sont renvoyes sur la base de 3 chiffres en octal:
        le premier octal contient les permissions de l'utilisateur,le deuxieme celles du groupe,le dernier celles des autres.
        7 : acces en lecture/ecriture/execution
        6 : acces en lecture/ecriture
        5 : acces en ecriture/execution
        4 : acces en lecture
        3 : acces execution/ecriture
        2 : acces ecriture
        1 : acces execution

4. Les macros POSIX qui le permettent sont:
    S_ISREG(m)
    S_ISDIR(m)
    S_ISCHR(m)
    S_ISBLK(m)
    S_ISFIFO(m)
    S_ISLNK(m)
    S_ISSOCK(m)


## Exercice 2

1. On peut filtrer ces noms de fichiers avec la fonction fnmatch.

2. Quelles sont les constantes POSIX permettant d'accéder aux différents bits de st_mode ?

 Les constantes POSIX sont : 
	S_ISDIR
	S_IRUSR
	S_IWUSR
	S_IXUSR
	S_IRGRP
	S_IWGRP
	S_IXGRP
	S_IROTH
	S_IWOTH
	S_IXOTH



## Exercice 3

1. Comment gérer l'aspect récursif de l'affichage des fichiers dans les sous-répertoires ?
	En programmant le programme de maniere a ce que quand on se trouve dans un repertoire un nouveau appel a ls_rec est fait.

2. Quelle doit être la taille de buffer à passer en deuxième paramètre de snprintf ?
	Le buffer doit etre de la meme taille que la nouvelle chaine créee qu'on recupere avec sizeof(nom_nouvelle_chaine)

3. Comment détecter une erreur sur l'appel à readdir ?
	Si readdir rencontre une erreur il renvoie null, on doit tester ce cas.
4. Comment effectuer la gestion des erreurs avec readdir ?
	Dans le cas ou readdir renvoie null on 

## Exercice 4

1. Détailler la stratégie employée pour effectuer la recherche de chaîne au sein d'un fichier.

	J'ouvre mon repertoire et je regarde tout d'abord s'il n'est pas vide.
	S'il ne l'est pas je le parcours entierement en creant les nouveaux chemins. Si le fichier est regulier , je l'ouvre et je cherche la chaine de caractere passée en paramètre grace a la fonction strstr. Si le fichier est un repertoire je lance de maniere recursive le programme sur le repertoire trouvé.

