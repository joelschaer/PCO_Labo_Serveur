# [PCO] labo 7 Serveur
## Étape 2

### Remarques
La taille idéale pour le ThreadPool est en corrélation avec le nombre de pocesseur disponnible sur la machine. Le processeur pourra au maximum threater un nombre de requêtes éguale au nombre de processeurs disponnible.
En choisissant le même nombre, les requêtes seront traitée entièrement avant de passer à la suivante et un réponse pourra donc être retournée le plus vite possible.

On souligne effectivement une amélioration de la stabilité. En effet, si on démarre maintenant un très grand nombre de requêtes, le serveur va prendre un peu de temps pour les traiter toutes, mais ne va se retouvé innondé. Il drop les requêtes si elles dépassent le nombre possible dans le buffer de requêtes et traite ces dernières progressivement sur un nombre de thread fix. Donc pas de création exessives de requêtes.

