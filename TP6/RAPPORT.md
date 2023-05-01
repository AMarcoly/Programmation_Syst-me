## Exercice 1

**Questions:**

1. Dans quel cas une écriture dans un tube est bloquante ?
    
    Une ecriture dans un tube est bloquante lorsque le tube est plein i-e le buffer de lecture est rempli et n'a pas encore ete lu pr liberer l'espace.

2. Dans quel cas une lecture dans un tube est bloquante ?

    Une lecture dans un tube est bloquante lorsque le tube est ouvert en ecriture.
    