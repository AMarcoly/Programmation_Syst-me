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

    Une section critique est une partie de code qui doit être exécutée sans interruption par d'autres processus ou threads pour éviter les conflits d'accès ou des incohérences dans les données manipulées.

2. Quelle partie du main est en section critique ?

    La partie du main qui est en section critique est la bouche while qui attend le signal 5 fois.
        Ligne 