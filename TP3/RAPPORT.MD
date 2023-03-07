## Exercice 1

**Questions :**

1. Comment faire pour que le processus père affiche son message toujours *après* le processus fils ?
2. Comment modifier le programme pour que le fils devienne  zombie ?
3. Comment modifier le programme pour que le fils devienne orphelin ?

1. Pour avoir le message du père qui s'affiche toujours apres il faut utiliser la primitive wait qui va permettre au père d'attendre la fin du processus fils. On le met avant les print.

2. Pour que le fils devienne zombie on met une boucle infinie dans le père. while(1) 

3. utiliser sleep pr etre sur que le pere attende.

processus orphelin pas termine. zombie termine. Mettre un exit a la fin du fils. 
si mettre exit il 

##  Exercice 2

# Question 1
L'ordre d'affichage ne suit pas l'ordre de creation.
# Question 2
Ce qui est normal car l'ordonanceur lance les processus selon le quantum du systeme.
Lorsque l'ordonanceur passe au processus fils 2 le processus 1 n'a pas eu le temps de finir et entre temps le processus 2 se termine. Et on revient au processus 1 qui se termine a son tour.


"Si argument passe n'est pas un repertoire exit: pour projet. Pour executable faire "