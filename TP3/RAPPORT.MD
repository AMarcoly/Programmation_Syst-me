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


