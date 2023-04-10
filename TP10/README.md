# Séance 10 - Signaux POSIX

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
unsigned alarm(unsigned seconds);
unsigned int sleep(unsigned int seconds); 
```


Objectifs de ce TP :
* savoir manipuler les signaux avec les primitives POSIX
* comprendre la notion de traitement asynchrone
* appréhender la notion de concurrence et de section critique
* comprendre la notion de masquage de signaux

## Exercice 1 
Écrivez un programme `proc_alarm.c` composé de deux processus. Le processus père génère un processus fils qui doit exécuter une fonction `traite` toutes les secondes, qui ne fait qu’afficher un message avec la primitive `write(STDOUT_FILENO,...)` (la fonction `printf` **ne doit pas** être utilisée dans une fonction traitante associée à un signal, la fonction n'étant pas *réentrante*).

Le processus père s'endort pendant 10 secondes puis prévient le fils qu’il doit s’arrêter en lui envoyant le signal `SIGUSR1`. Lorsque le processus fils reçoit l’ordre du père, il affiche un message et s’arrête effectivement, provoquant alors la terminaison du père. 

Vous utiliserez la primitive `alarm` pour la temporisation.

**Questions:**
- pourquoi faut-il faire appel à `sigaction` avant l'appel à `fork`?
- si on fait l'appel à `sigaction` dans le fils, que pourrait-il arriver ?

