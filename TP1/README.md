# Séance 1 - Fichiers

En programmation système, il existe deux types de primitives pour manipuler les fichiers :

1. Les primitives dites « système » car elles correspondent à des appels système du noyau :

    ```c
    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);
    ssize_t read(int fd, void *buf, size_t count);
    ssize_t write(int fd, const void *buf, size_t count);
    int close(int fd);
    off_t lseek(int fd, off_t offset, int whence);
    ```
2. Les fonctions de bibliothèque dont les prototypes sont décrits dans le fichier `<stdio.h>`, qui sont des fonctions d'entrée/sortie de plus haut-niveau qui utilisent un buffer interne (caché à l'utilisateur). Elles s'appuient sur les primitives système ci-dessus mais ne correspondent pas à des appels système du noyau :
    ```c
    FILE *fopen(const char *path, const char *mode);
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    int fgetc(FILE *stream);
    int fputc(int c, FILE *stream);
    int fclose(FILE *fp);
    int fseek(FILE *stream, long offset, int whence);
    ```

Pour savoir quels fichiers `.h` inclure et avoir des informations détaillées sur le rôle et l'utilisation de ces fonctions utiliser la commande `man` :

```sh
man fopen
man 2 open    # car `man open` affiche l'aide sur la commande système `open`
```

L'objectif de ce TP est de se familiariser avec ces deux types de primitives, de savoir les utiliser à bon escient et de ne pas les confondre.

## Bonnes pratiques

* Pour réaliser ces TP, vous mettrez en œuvre les bonnes pratiques de programmation énoncées ici : https://pdagog.gitlab.io/ens/conseils.pdf
* Les erreurs retournées par les primitives systèmes seront systématiquement testées, soit à l'aide de la fonction `raler`, soit avec la macro `CHK`:
https://moodle.unistra.fr/pluginfile.php/230879/mod_resource/content/3/fonction_raler.c
* Dans chaque répertoire de TP, vous écrirez un fichier `Makefile` permettant de compiler l'ensemble des fichiers du TP, ainsi qu'une cible `clean`
* Dans chaque répertoire de TP, vous écrirez un court rapport `rapport.md` au format Markdown dans lesquel vous répondrez aux différentes questions du sujet de TP.
* Vous effectuerez des `commit` réguliers de votre travail, et un `push` en fin de séance.

## Exercice 1 

En utilisant uniquement les primitives système, écrire le programme `cp_sys` qui prend deux noms de fichier en paramètres et recopie le contenu du premier fichier dans le second, octet par octet.
Si `fichier2` n'existe pas, le programme le créera avec les droits `0666`.

Tester votre programme en vérifiant que les deux fichiers sont identiques (commande `cmp`).

```sh
./cp_sys <fichier1> <fichier2> 
```

**Questions :**

1. Dans quel fichier `man` se trouvent les informations sur les constantes `flags` correspondant au deuxième paramètre de `open` ?
2. Dans quel fichier `man` se trouvent les informations sur les constantes `mode_t` correspondant au troisième paramètre de `open` ?
3. Que se passe-t-il si le deuxième fichier n'existe pas et que le programme omet de le créer ?
4. Que se passe-t-il si le deuxième fichier est créé mais que le programme omet de spécifier ses permissions ?

## Exercice 2

Écrire le programme `cp_std` qui recopie le contenu du premier fichier dans le second fichier passé en paramètre, mais en utilisant cette fois les fonctions de bibliothèque `fgetc()` et `fputc()`.

```sh
./cp_std <fichier1> <fichier2>
```

**Questions :**

1. Dans quel fichier `man` se trouvent les informations sur les valeurs possibles correspondant au deuxième paramètre de `fopen` ?
2. Que se passe-t-il si le deuxième fichier n'existe pas ?
3. Qu'est-ce que la constante `EOF` ? Est-ce qu'elle correspond à un caractère présent dans le fichier ?


## Exercice 3

Créer un fichier de grande taille en utilisant (par exemple) la commande :

```sh
dd if=/dev/urandom of=bigfile count=50000
```

1. A l'aide de la commande `time`,  comparer les temps de copie de ce fichier avec `cp_sys` et `cp_std`.
2. Modifier `cp_sys` de manière à ajouter un troisième paramètre, qui sera une constante entière qui déterminera la taille du buffer utilisé pour la copie du fichier :

    ```sh
    ./cp_sys <fichier1> <fichier2> <taille_buffer>
    ```
3. Déterminer de manière expérimentale la taille de buffer permettant de minimiser le temps de copie de ce fichier volumineux.

**Questions :**

1. Donner sous forme de tableau le résultat de vos expérimentations :

    | Temps `cp_std` (ms) |
    |:----------------:|
    | ... |

    |Taille du buffer (octets) | Temps `cp_sys` (ms) |
    |:----------------:|:--------------:|
    |  1               |  ...             |
    |  8             | ...          |
    |  16             | ...          |
    |  256             | ...          |
    |  512             |  ...          |
    |  1024             |  ...            |
    |  ...             |  ...             |

2. Quelle est la taille du buffer utilisé par les fonctions de bibliothèque ?

## Exercice 4

Écrire le programme `cp_rev` qui écrit, caractère par caractère,  le contenu du premier fichier dans le second, mais dans l'ordre inverse (le dernier octet est écrit en première position, l'avant dernier en deuxième position, etc.). Vous utiliserez les primitives système.

Vérifier à l'aide de la commande `cmp` qu'un fichier inversé deux fois est bien identique à l'original.

```sh
./cp_rev <fichier1> <fichier2> 
```

**Questions :**

1. Comment positionner la tête de lecture à la fin du fichier ?
2. Comment faire « reculer » la tête de lecture ?
2. Quelles sont les différentes possibilités pour connaître la taille d'un fichier ?

## Exercice 5 

Écrire les programmes `read_int` et `write_int` qui permettent, respectivement, de lire  et d'écrire un entier de type `int64_t` (codé sur $`64`$ bits, faites un `#include <stdint.h>`) à une position donnée dans un fichier passé en paramètre, à l'aide des primitives système.

Le programme `read_int` affiche l'entier présent à la position `pos` du fichier. 

Le programme `write_int` écrit dans un fichier existant le nombre décimal donné en troisième argument de la commande à la position `pos`. Si le fichier n'existe pas, il est créé avec les droits `0666`. Si `pos` dépasse la taille du fichier, le fichier sera complété avec des `0`.

Tester vos programmes en vérifiant qu'un entier écrit avec `write_int` est correctement lu avec `read_int`. Vous pourrez vous aider de la commande `hexdump`  afin de visualiser le contenu de vos fichiers.

```sh
./read_int <fichier> <pos> 
./write_int <fichier> <pos> <entier>
```

**Questions :**

1. Que se passe-t-il si on essaie de lire à une position de valeur négative ?
2. Que se passe-t-il si on essaie de lire au delà de la fin du fichier ?
3. Comment faire pour afficher une erreur dans ce cas ?
4. Que se passe-t-il si on écrit au delà de la fin du fichier ?
