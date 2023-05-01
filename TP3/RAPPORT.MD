## Exercice 1

**Questions :**

1. Comment faire pour que le processus père affiche son message toujours *après* le processus fils ?

    Pour avoir le message du père qui s'affiche toujours apres il faut utiliser la primitive wait qui va permettre au père d'attendre la fin du processus fils. On le met avant les print.


2. Comment modifier le programme pour que le fils devienne  zombie ?
   
    Pour que le fils devienne zombie on met une boucle infinie dans le père. while(1) , le processus fils se termine et attend dans la table des processus un wait. 

3. Comment modifier le programme pour que le fils devienne orphelin ?
    
    Pour que le fils devienne orphelin on utilise sleep pr etre sur que le pere attende mais moins de temps que le fils.
    Le pere n'attend pas so fils qui est immediatement apparente a sa terminaison au processus 1.

##  Exercice 2

**Questions :**

1. Que peut-on dire de l'ordre d'affichage des codes des processus fils dans le père ?
    
    L'ordre d'affichage ne suit pas l'ordre de creation.
2. Comment expliquer cela ?
    
    Ce qui est normal car l'ordonanceur lance les processus selon le quantum du systeme.
    Lorsque l'ordonanceur passe au processus fils 2 le processus 1 n'a pas eu le temps de finir et entre temps le processus 2 se termine. Et on revient au processus 1 qui se termine a son tour.


## Exercice 3

**Questions:**

1. Comment utiliser execvp avec les arguments passés en ligne de commande et stockés dans le tableau char *argv[] ?
    
    Pour gerer cela, j'ai cree dans le code avant le `fork` un tableau de meme taille que le nombre d'arguments places en parametres.
    Le premier argument est le nom de la fonction, le second la commande Unix suivi de la liste de ses parametres.
    Ainsi, je peux me servir de ce tableau pour faire appel a la commande execvp.
    
2. Dans quel cas le processus fils renvoie le code 1 (=EXIT_FAILURE) ?
    
    Le processus fils renvoie 1 si la commande Unix place en parametre est bon mais pas ses parametres.

## Exercice 4
**Questions:**

1. Exécuter le programme en redirigeant la sortie standard vers un fichier :
    Ce fichier est-il bien formé ? Comment expliquer le résultat ?
        
        R-
    Comparer le nombre de caractères effectivement écrits sur la sortie standard avec le nombre de caractères lus.
       
        R-

2. Que se passe-t-il lorsque le fichier est ouvert après l’appel à fork ?

    Si le processus fils ouvre un fichier après l'appel à fork, il ouvre une nouvelle copie indépendante du descripteur de fichier dans sa propre table de descripteurs de fichiers. Les modifications apportées au descripteur de fichier par le processus fils n'affecteront pas le descripteur de fichier dans le processus père.

## Exercice 5
**Questions:**

1. Combien de processus doivent être créés ?

    On doit creer trois processus fils. Un pour gerer la premiere partie de la commande jusqu'a `;` et les deux autres la seconde partie.

2. Comment gérer dans votre programme les redirections de l'entrée et de la sortie standard ?

    Grace a la commande dup2 on peut gerer les redirections d'entree et de sortie.
    Dans fils 1 on fait une premiere redirection `ps eaux > toto`.
        Ligne 38 a 47 du code.
    Dans le fils 2 on gere la redirection `grep "username" < toto > /dev/null` i-e on redirige entree standard vers toto et sortie standard vers /dev/null.
        Ligne de code 53 a 77

3.  Comment gérer dans votre programme le caractère `;` du script ?

    On gere ce caracte avec un waitpid ligne 50 , on attend fils 1 se termine avant de poursuivre le reste du programme.

4. Comment gérer dans votre programme les caractères && du script ?

    On gere le && avec un waitpid + un controle sur la raison envoye par le fils 2. Le fils 3 ne s'execute que si le fils 2 a fini de s"executer mais a reussi son execution.
        Gestion : ligne de code 83 a 90.



