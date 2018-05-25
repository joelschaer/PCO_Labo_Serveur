# [PCO] labo 5 Serveur
## Étape 1
Dans cette étape nous avons séparer le traitement des requêtes avec un système de threading.

### BufferN
Cette classe est une classe générique qui dérive de l'interface AbstractBuffer. Elle implémente un tableau d'elements d'une taille donnée et permet d'y déposer et d'y lire des données à l'aide des fonctions "put" et "get". Elle utilise les moniteurs de Hoare pour la gerstion de l'exclusion mutuelle.

### RequestDispatcherThread
Cette classe threadée implémente le dispatcher de requêtes. Il récupère les requêtes depuis le buffer de requêtes (buffer d'entrée) et démarre un thread pour chacune d'elle. Chaque thread va traiter une requête qui lui est attribuée.

### RequestProcessing
Cette classe est chargée de traiter la requête qui lui est transmise dans un thread séparé et de rendre la réponse dans le buffer de réponses (buffer de sortie).

### Remarques
Nous pouvons remarquer avec cette méthode que l'exécution se fait effectivement en paralèlle et le serveur est donc capable de gérer un certain nombre de requêtes simultanément. Il n'est plus nécessaire d'attendre le temps d'exécution successif des tâches mais une exécution parallèle. L'exécution est plus rapide qu'avec la version non threadée.

La charge qui peut être supportée reste cependant limitée. En effet si on lance beaucoup de requête chacune va démarrer un thread et ouvrir une fois la ressource. A partir d'un certain nombre le serveur crache car il ne peut pas ouvrir trop de fois le fichier en même temps. Cela à également pour conséquence si on attend pas cette valeur de charger énormément le processeur.

Pour éviter de surchager la machine en démarrant autant de threads que de requête il faudrait fixer une limite afin que seul un nombre raisonnable de threads soit exécutés et que les autres attendent la fin de l'exécution des précédents.
