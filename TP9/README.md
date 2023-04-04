# Séance 9 - Signaux POSIX

Primitives utilsées dans ce TP :

```c
int sigaction (int sig, const struct sigaction ⁎new, struct sigaction old);
int sigsuspend(const sigset_t *sigmask);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
```

```c
unsigned int sleep(unsigned int seconds); 
```


Objectifs de ce TP :
* savoir manipuler les signaux avec les primitives POSIX
* comprendre la notion de traitement asynchrone
* appréhender la notion de concurrence et de section critique
* comprendre la notion de masquage de signaux

## Exercice 1 : attente active / passive

Écrivez le programme `ecoute_active.c` qui, à chaque réception du signal `SIGUSR1`, affiche un message sur la sortie standard avec `write`. L'attente du signal s'effectue de manière active à l'aide d'une boucle infinie.

Écrivez le programme `ecoute_passive.c` qui fait la même chose que le programme précédent mais en utilisant une attente passive à l'aide de la primitive `sigsuspend`.

Lancez votre programme avec `&` pour le mettre en arrière plan, puis utilisez la commande `kill` pour envoyer au processus le signal `SIGUSR1`.

**Questions :**

1. Quelle est la différence entre écoute active et écoute passive ?
2. Quelle solution est à proscrire et pourquoi ?


## Exercice 2 : liste des signaux

Écrivez un programme qui attend l’arrivée d’un signal (n’importe lequel), affiche sa signification (par exemple : `illegal instruction` pour `SIGILL`)  puis se termine.
Vous pouvez utiliser la fonction de bibliothèque `psignal` pour afficher la signification d’un signal.
Vous testerez votre programme avec la commande `kill`.

**Question :**

1. Quels sont les signaux dont il est impossible de modifier l'action par défaut et pourquoi ?


## Exercice 3 : compteur

Écrivez le programme `compteur.c` qui incrémente et affiche un compteur à chaque fois qu’il reçoit le signal `SIGINT`. Au bout de 5 fois, il doit s’arrêter. L’incrémentation et l’affichage du compteur ne doivent pas être réalisés dans la fonction `main`.
Vous prendrez garde de masquer le signal `SIGINT` dans le `main` pendant la section critique.

**Questions :**
1. Qu'appelle-t-on *section critique* ? 
2. Quelle partie du `main` est en section critique ?


## Exercice 4 : masquage de signaux

Écrivez un programme `masque.c` qui, à la réception du signal `SIGINT`, affiche un message avec `write(1,MSG,strlen(MSG))`, où `MSG` est une constante (vous ne devez pas utiliser `printf`). Après la mise en place de la fonction associée au signal, le programme :

- attend trois secondes (avec `sleep`)
- masque le signal `SIGINT` avec `sigprocmask` puis attend 3 secondes
- démasque le signal `SIGINT`
- attend 3 secondes
- se termine normalement

Lancez ce programme et utilisez `Ctrl-C` pour envoyer (éventuellement plusieurs fois) le signal au programme, et cela durant les différentes phases (avant, pendant et après le masquage). 

Avant de répondre aux questions, lisez attentivement la page `man` de la primitive `sleep`.

**Questions:**

1. Que se passe-t-il si le signal arrive avant le masquage, pendant le premier appel à `sleep` ?

2. Que se passe-t-il s'il arrive après le masquage-démasquage, pendant le troisième appel de `sleep` ?

3. Que se passe-t-il si le signal arrive (une seule fois) pendant que le signal est masqué ? 

4. Que se passe-t-il si le signal arrive plusieurs fois dans cet intervalle ?

5. Si la fonction `sleep` est interrompue, elle renvoie une valeur non-nulle égale au nombre de secondes restant normalement à attendre. Modifiez votre programme pour rappeler `sleep()` si le délai n’est pas écoulé en retour de l’appel.

6. Modifiez votre programme pour que le signal puisse être reçu plusieurs fois avant le masquage, ou après le masquage.

