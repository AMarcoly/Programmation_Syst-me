# Séance 3 - Processus

Primitives utilsées dans ce TP :

```c
pid_t fork(void);
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int dup(int oldfd);
int dup2(int oldfd, int newfd);
pid_t getpid(void);
pid_t getppid(void);
```

Famille des fonctions `exec()` :

```c
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char * const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *file, char *const argv[], char *const envp[]);
```

Objectifs de ce TP :
* appréhender la notion de processus en programmation système
* savoir manipuler la primitive `fork` et la synchronisation entre processus
* savoir effectuer des redirections au travers des primitives `dup()` et `dup2()`.

## Bonnes pratiques

* Pour réaliser ces TP, vous mettrez en œuvre les bonnes pratiques de programmation énoncées ici : https://pdagog.gitlab.io/ens/conseils.pdf
* Les erreurs retournées par les primitives systèmes seront systématiquement testées, soit à l'aide de la fonction `raler`, soit avec la macro `CHK`:
https://moodle.unistra.fr/pluginfile.php/230879/mod_resource/content/3/fonction_raler.c
* Dans chaque répertoire de TP, vous écrirez un fichier `Makefile` permettant de compiler l'ensemble des fichiers du TP, ainsi qu'une cible `clean`
* Dans chaque répertoire de TP, vous écrirez un court rapport `rapport.md` au format Markdown dans lesquel vous répondrez aux différentes questions du sujet de TP.
* Vous effectuerez des `commit` réguliers de votre travail, et un `push` en fin de séance.

## Exercice 1 

Écrire le programme `fork1` qui crée un processus fils :
* le processus fils affiche son numéro de PID ainsi que celui du père, puis se termine en retournant un code  égal au dernier chiffre de son PID.
* le père affiche son numéro de PID ainsi que celui de son fils, attend la terminaison du fils puis affiche le code de retour du fils.

**Questions :**

1. Comment faire pour que le processus père affiche son message toujours *après* le processus fils ?
2. Comment modifier le programme pour que le fils devienne  zombie ?
3. Comment modifier le programme pour que le fils devienne orphelin ?

## Exercice 2

Écrire le programme `fork2` qui prend en paramètre un entier `n`. Le programme crée dans une première étape `n` processus fils numérotés de $`0`$ à $`n-1`$ puis, dans une seconde étape, attend leur terminaison. Chaque processus fils se termine en retournant un code correspondant à son ordre de lancement. Dès qu'un processus se termine, le père affiche son PID et son code de retour.

**Questions :**

1. Que peut-on dire de l'ordre d'affichage des codes des processus fils dans le père ?
2. Comment expliquer cela ?


## Exercice 3

Écrire le programme `run` qui prend en paramètre un nom de commande Unix suivi de ses paramètres, puis crée un processus fils qui exécute cette commande à l'aide de `execvp`.
Le processus père attend la terminaison de son fils puis affiche le code de retour du fils. Si la commande Unix donnée en paramètre n'est pas une commande valide, le processus fils retourne le code 2.

Exemple :

```
./run wc -l run.c

34 run.c
Mon fils s'est terminé avec le code : 0
```

**Questions :**

1. Comment utiliser `execvp` avec les arguments passés en ligne de commande et stockés dans le tableau `char *argv[]` ?
2. Dans quel cas le processus fils renvoie le code 1 (=`EXIT_FAILURE`) ?

## Exercice 4

Écrire le programme `fork3`  qui prend un nom de fichier en paramètre et qui :
1. ouvre le fichier en lecture;
2. créé un processus fils;
3. puis les deux processus (père et fils) lisent les caractères l’un après l’autre dans le fichier en utilisant la primitive système `read`, et les écrivent avec `write` sur la sortie standard.

Expérimentez ce programme avec un fichier texte de taille assez grande. 

**Questions :**

1. Exécuter le programme en redirigeant la sortie standard vers un fichier :
    1. Ce fichier est-il bien formé ? Comment expliquer le résultat ?
    2. Comparer le nombre de caractères effectivement écrits sur la sortie standard avec le nombre de caractères lus.
2. Que se passe-t-il lorsque le fichier est ouvert *après* l’appel à `fork` ?


## Exercice 5

Écrivez un programme `script.c` équivalent au script shell suivant, qui prend en argument un nom d’utilisateur :

```sh
ps eaux > toto ; grep "^$1 " < toto > /dev/null && echo "$1 est connecté"
```

Votre programme devra :

* réaliser effectivement les exécutions de `ps` et `grep` en utilisant la primitive `execlp` ;
* mettre en place les redirections des entrées/sorties nécessaires grâce à la primitive `dup` (ou `dup2`) ;
* réaliser l’affichage final avec la primitive `write`.

**Questions :**

1. Combien de processus doivent être créés ?
2. Comment gérer dans votre programme les redirections de l'entrée et de la sortie standard ?
2. Comment gérer dans votre programme le caractère `;` du script ?
3. Comment gérer dans votre programme les caractères `&&` du script ?
