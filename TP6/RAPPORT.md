## Exercice 1

**Questions:**

1. Dans quel cas une écriture dans un tube est bloquante ?
    
    Une ecriture dans un tube est bloquante lorsque le tube est plein i-e le buffer de lecture est rempli et n'a pas encore ete lu pr liberer l'espace.

2. Dans quel cas une lecture dans un tube est bloquante ?

    Une lecture dans un tube est bloquante lorsque le tube est vide , aucune donnee n'a encore ete ecrite dans le tube cote lecture.

3. Que se passe-t-il quand un processus effectue une écriture dans un tube sur lequel il n'y a aucun lecteur ?
    Lorsqu'une processus essaie d'ecrire dans un tube sans lecteur, l'information est stockee dans le buffer d'ecriture en attendant un lecture.
    Si on ferme le cote en ecriture avant qu'un lecture ne lise le buffer, lorsq'on essaiera de lire on aura un message specifiant la fin du fichier.

4. Dans le programme pipe_c.c que se passe-t-il si le père ne ferme pas l'extrémité en écriture du tube ? Pourquoi ?
    Le programme continue normalement car la lecture est bloquante de maniere automatique.

