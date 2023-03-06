# TP à rendre - Processus 

## Cahier des charges

Écrivez le programme `exdir` qui admet un argument (le nom
d'un répertoire) et exécute la commande `file` avec l'option
`--mime-type` sur tous les fichiers exécutables contenus dans
ce répertoire. 

Par exemple :

```sh
dusse@turing:~ ./exdir /usr/bin
```

doit exécuter la commande `file --mime-type` (via un appel à
la fonction `execvp`) sur tous les fichiers exécutables
contenus dans le répertoire `/usr/bin`.

Si l'argument donné n'est pas un répertoire accessible en exécution par l'utilisateur, le programme renvoie un code d'erreur non nul et affiche un message sur la sortie erreur standard.

Votre programme devra traiter chaque type de fichier de la manière
suivante :

* chaque fichier régulier rencontré sera traité s'il est
    accessible et exécutable par l'utilisateur courant. Sinon, le
    fichier sera ignoré

* si le fichier est un répertoire accessible à l'utilisateur, le traitement se poursuivra dans ce répertoire. Sinon, le répertoire sera ignoré

*  les autres types de fichiers seront ignorés (cela inclut en particulier les liens symboliques)

Le résultat de chaque appel à la commande `file` devra être
redirigé vers un fichier du même nom que le fichier exécutable
traité. 

Par exemple la sortie de l'appel à :

```console
file --mime-type unFichierExecutable
```

devra être redirigée dans un fichier `unFichierExecutable`. 

Tous les fichiers ainsi générés devront être placés dans le répertoire `/tmp/uid` où `uid` correspond au numéro d'utilisateur courant. Pour simplifier l'exercice on supposera qu'il n'y a pas deux programmes de même nom dans l'ensemble du répertoire.

Lorsque tous les fichiers du répertoire passé en paramètre auront été
traités, votre programme se terminera avec un code de retour nul si
tout s'est bien passé, ou non nul si un problème a été rencontré. En
outre, si un problème survient sur un fichier, votre programme devra
notifier l'utilisateur du problème et passer au fichier suivant.

Pour résumer :

1. si le programme est appelé sur un répertoire non accessible en exécution par l'utilisateur, il doit quitter et retourner un code non nul

2. si le programme trouve un sous-répertoire non accessible en lecture   *ou*  non accessible en exécution (i.e. non « traversable »), il doit l'ignorer silencieusement

Enfin si la taille du chemin d'accès à un fichier dépasse `PATH_MAX` caractères, le programme s'arrête et retourne un code d'erreur non nul.


Vous écrirez le programme `exdir` en langage C en n'utilisant
que des primitives système ; vous pouvez utiliser des fonctions de
bibliothèque pour l'affichage, la gestion des chaînes de caractères et
le parcours de répertoire (`opendir`, `readdir`, `closedir`). La
fonction `execvp` est ici assimilée à une primitive
système.

## Modalités de rendu

Vous devrez déposer sur votre git, **ainsi que sur Moodle dans le répertoire de dépôt dédié**, un unique fichier `exdir.c`.

Votre programme devra compiler avec `cc -Wall -Wextra -Werror`.
Les programmes qui ne compileront pas avec cette commande ne seront pas
examinés. Votre programme devra libérer toute la mémoire allouée.

## Date limite 

Vous devrez rendre votre travail avant le **lundi 13 mars 17h00**

## Script de notation

Un script de notation est mis à votre disposition dans ce dépôt. Celui-ci
compile votre programme et l'exécute sur des jeux de tests. Il vous
affiche la note (sur 4 points) qui servira de base à l'évaluation de
votre rendu. N'hésitez pas à lire ces tests et le fichier de *log*
généré : ils peuvent vous aider à mettre votre programme au point.

Ce TP à rendre est individuel. On rappelle que la copie ou le plagiat
sont sévèrement sanctionnés.

