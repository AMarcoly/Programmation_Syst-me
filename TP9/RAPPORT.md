## Exercice 1
**Question:**

1. Quelle est la différence entre écoute active et écoute passive ?

    L'écoute active est une méthode où la machine surveille activement(sans discontinuite) un message/signal, tandis que l'écoute passive est une méthode où la machine ne suirveille pas l'attende d'un signal de maniere continue mais attend qu'une demande soit envoyee/recue.

2. Quelle solution est à proscrire et pourquoi ?

    L'ecoute active est a proscrire car le processus monopolise du temps processeur pour ne rien faire.
    C'est energivore. 

## Exercice 2

**Questions:**

1. Quels sont les signaux dont il est impossible de modifier l'action par défaut et pourquoi ?

    Les signaux impossible de modifier l'action par defaut sont : SIGKILL, SIGSTOP.
    Ces signaux ne peuvent etre modifies car ces signaux sont reserves au systeme d'exploitation ainsi que ses processus.

## Exercice 3

**Question:**

1. Qu'appelle-t-on section critique ?

    Une section critique est une partie de code qui doit être exécutée sans interruption par d'autres processus pour éviter les conflits d'accès ou des incohérences dans les données manipulées.
    Les signaux y sont masques.

2. Quelle partie du main est en section critique ?

    La partie du main qui est en section critique est la partie entre les deux primitives sigprocmask
        Le signal est masque dans cette partie .

## Exercice 5

**Questions:**

1. Si le signal arrive avant le masquage, pendant le premier appel à sleep, le programme sera interrompu et la fonction associée au signal sera appelée. La fonction affichera le message et le programme se terminera immédiatement.

2. Le signal sera traité normalement et la fonction associée sera appelée pour afficher le message MSG. Le signal ne sera pas masqué, car le masquage a déjà été annulé. Le signal pourra être de nouveau reçu et traité normalement. 
Après l'affichage du message, le programme attendra la fin du délai de sleep avant de se terminer normalement.

3. Si le signal arrive pendant que le signal est masqué, il ne sera pas traité immédiatement car il est masqué. Le signal sera en attente jusqu'à ce que le masquage soit annulé. Une fois le signal démasqué, le signal sera traité normalement et la fonction sera appelée pour afficher le message `MSG`. Le programme attendra la fin du délai de sleep avant de se terminer normalement.

4. 