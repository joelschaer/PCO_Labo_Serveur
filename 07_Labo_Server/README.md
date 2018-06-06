# [PCO] labo 7 Serveur
## Étape 2
Ce programme à pour but de traiter les requêtes qui lui sont transmises afin de retourner le fichier demander si celui-ci existe.
Pour ce faire nous disposons d'un tampon de requêtes qui va recevoir toutes les requêtes que le serveur reçoi. Ces requêtes sont ensuite récupéréer par un request dispatcher. 
Celui-ci travail sous la forme d'un thread qui à pour objectif de transmettre les demande au threads de travail. Ces threads de travails sont regroupé sous la forme d'un thread pool.
Chaque thread de travail se voit remettre un tâche dès que celui-ci est disponnible. 
Une fois termié la réponse que remise dans un tampon avant d'être retournée vers le client par le response dispatcher.

### ThreadPool
Le ThreadPool dispose d'un certains nombre d'objets Threads auquels il peut, si ces derniers sont disponnble une tâche à réaliser.
Le nombre de threads qu'il peut créer est fixé à la création.s

### Thread
Est une classe interne du Thread Pool. Ce sont des objets qui ont pour tâche d'exécuter le travail qui leur est remis et de se manifester comme disponnbile auprès du threadpool une fois le travail terminé.
Les threads disponnbiles sont gardé dans un bufferN créé à l'étape précédente les pointeurs vers ces threads sont ainsi retiré du buffer lorsqu'ils sont occupé et remis quand ils sont libre.
Un thread ne se verra ainsi jamais attribuer une tâche s'il est déjà occupé.


### Réponse aux questions.
La taille idéale pour le ThreadPool est en corrélation avec le nombre de pocesseur disponnible sur la machine. Le processeur pourra au maximum traiter un nombre de requêtes éguale au nombre de processeurs disponnible.
En choisissant le même nombre, les requêtes seront traitée entièrement avant de passer à la suivante et une réponse pourra donc être retournée le plus vite possible vers le client.

On souligne effectivement une amélioration de la stabilité. En effet, si on démarre maintenant un très grand nombre de requêtes, le serveur va prendre un peu de temps pour les traiter toutes, mais ne va pas se retouvé innondé et cracher. Il drop les requêtes si elles dépassent le nombre possible dans le buffer de requêtes et traite ces dernières progressivement sur un nombre de threads fix. Donc pas de création exessives de requêtes.

