# Séance 2 - Attributs des fichiers, répertoires


Primitives utilsées dans ce TP :

```c
int stat (const char ⁎path, struct stat ⁎stbuf);
int fstat (int fd, struct stat ⁎stbuf);
```

```c
DIR ⁎opendir (const char ⁎path);
struct dirent ⁎readdir (DIR ⁎dp);
int closedir (DIR ⁎dp);
```

Objectifs de ce TP :
* savoir manipuler la structure `stat` permettant de récupérer les attributs des fichiers
* savoir manipuler les structures `DIR` et `dirent` pour la gestion des répertoires 

## Bonnes pratiques

* Pour réaliser ces TP, vous mettrez en œuvre les bonnes pratiques de programmation énoncées ici : https://pdagog.gitlab.io/ens/conseils.pdf
* Les erreurs retournées par les primitives systèmes seront systématiquement testées, soit à l'aide de la fonction `raler`, soit avec la macro `CHK`:
https://moodle.unistra.fr/pluginfile.php/230879/mod_resource/content/3/fonction_raler.c
* Dans chaque répertoire de TP, vous écrirez un fichier `Makefile` permettant de compiler l'ensemble des fichiers du TP, ainsi qu'une cible `clean`
* Dans chaque répertoire de TP, vous écrirez un court rapport `rapport.md` au format Markdown dans lesquel vous répondrez aux différentes questions du sujet de TP.
* Vous effectuerez des `commit` réguliers de votre travail, et un `push` en fin de séance.

## Exercice 1 

Écrire le programme `my_stat` qui prend un nom de fichier en paramètre et affiche certains attributs liés à ce fichier.
On souhaite afficher les attributs suivants :

* l'UID et le GID du fichier 
* la taille  
* le type du fichier : "régulier" ou "répertoire" (on traitera uniquement ces deux cas)
* la représentation en **octal** des permissions du fichier

Exemple :

```sh
./my_stat README.md

UID : 501 
GID : 20 
File size : 4270 octets
Type : Régulier
Mode : 644
```

**Questions :**

1. Dans quel fichier `man` peut-on trouver la description de la structure `struct stat` ?
2. Quel attribut de la structure `stat` stocke les permissions du fichier et quelle opération effectuer afin de récuperer uniquement cette information ? 
3. Comment interpréter les permissions à partir de la représentation en base octale ?
4. Quelles sont les macros POSIX pour vérifier le type de fichier (dans le champ `st_mode`) ?

## Exercice 2

1. Écrire le programme `ls1`  qui affiche sur la sortie standard les fichiers présents dans le répertoire courant.
On prendra les mêmes conventions de restriction d’affichage que la commande `ls` (pas d’affichage des noms commençant par un point).

    Exemple :

    ```sh 
    ls1 
    README.md
    TP1
    TP2
    ```
2. Écrire le programme `ls2`, qui étend le programme précédent de manière à afficher les permissions de chaque fichier à la manière de `ls -l`.

    Exemple :

    ```sh 
    ls2
    -rw-r--r-- README.md
    drwxr-xr-x TP1
    drwxr-xr-x TP2
    ```


**Questions :**

1. À l'aide de quelle fonction de bibliothèque peut-on filtrer les noms de fichier qui commencent par un point ?
2. Quelles sont les constantes POSIX permettant d'accéder aux différents bits de `st_mode` ?

## Exercice 3

Écrire le programme `ls_rec` qui affiche sur la sortie standard les fichiers présents dans le répertoire passé en paramètre et tous les sous-répertoires, de manière récursive.

Pour concaténer deux chaînes de caractères, vous pourrez utiliser la fonction `snprintf`. 
Vous pourrez utiliser la constante `PATH_MAX` du fichier `<limits.h>` qui définit la taille maximale  d'un chemin.

Exemple :

```sh 
ls_rec PS/
PS/TP1 
PS/TP1/README.md
PS/TP2
PS/TP2/README.md
```

**Questions :**

1. Comment gérer l'aspect récursif de l'affichage des fichiers dans les sous-répertoires ?
2. Quelle doit être la taille de buffer à passer en deuxième paramètre de `snprintf` ?
3. Comment détecter une erreur sur l'appel à `readdir` ?
4. Comment effectuer la gestion des erreurs avec `readdir` ?

## Exercice 4

Écrire le programme `chercher_chaine` pour afficher tous les noms des fichiers d’une arborescence dont le contenu comprend une chaîne de caractères. Votre programme doit admettre la syntaxe suivante :

```sh 
chercher_chaine <chaîne> <répertoire>
```

Par exemple :

```sh 
./chercher_chaine "struct utimbuf" /usr/include

/usr/include/utime.h 
/usr/include/linux/utime.h
...
```
Vous utiliserez les primitives système pour rechercher la chaîne dans chaque fichier, en utilisant une méthode efficace (c'est à dire pas une lecture octet par octet). Pour afficher le nom de chaque fichier trouvé, vous pouvez utiliser la fonction de bibliothèque `printf`.

**Question :**

1. Détailler la stratégie employée pour effectuer la recherche de chaîne au sein d'un fichier.