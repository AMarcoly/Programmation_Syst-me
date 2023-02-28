## Question 1

**Questions :**

1. Comment faire pour que le processus père affiche son message toujours *après* le processus fils ?
2. Comment modifier le programme pour que le fils devienne  zombie ?
3. Comment modifier le programme pour que le fils devienne orphelin ?

1. Pour avoir le message du père qui s'affiche toujours apres il faut utiliser la primitive wait qui va permettre au père d'attendre la fin du processus fils. On le met avant les print.

2. Pour que le fils devienne zombie on met une boucle infinie dans le père. while(1) 

utiliser sleep pr etre sur que le pere attende.