# [PCO] labo 8 Serveur
## Étape 2
Ce programme à pour but de traiter les requêtes qui lui sont transmises afin de retourner le fichier demander si celui-ci existe.
Pour ce faire nous disposons d'un tampon de requêtes qui va recevoir toutes les requêtes que le serveur reçoi. Ces requêtes sont ensuite récupérées par un request dispatcher. 
Celui-ci travail sous la forme d'un thread qui à pour objectif de transmettre les demande au threads de travail. Ces threads de travails sont regroupé sous la forme d'un thread pool.
Chaque thread de travail se voit remettre un tâche dès que celui-ci est disponnible. 
Il va contrôler dans la cache si la requête aurait déjà été traite et transmet directement la réponse au tampon de sortie si c'est le cas. Autrement il procède au calcul de la réponse.
Une fois termié la réponse est remise dans un tampon avant d'être retournée vers le client par le response dispatcher.

### ReaderWriterCache
Une mémoire cache qui base la présence d'un élément sur sa présence dans une map. Chaque élément est une requête à la quelle est associé sa réponse calculée et un timestamp qui permet de gérer l'heure à laquelle la réponse à été générée. Une classe interne threadée précède au retrait des valeurs obsolètes de la cache.

### ReaderWriterLock
Permet de gérer l'accès concurent à la mémoir et de gérer la priorité à la lecture ou à l'écriture.

## Choix d'implémentation
Le producteur-consomateur que nous avons implémenté est basé sur la priorité à l'écriture. Nous avons fait ce choix afin d'assuer une valeur qui à déjà été calculée soit rendu disponnbile au lecteur dès que possible. De cette manière on évite qu'un valeur prête soit en attende alors que certains lecteur pourraient en avoir besoin.


### Réponse aux questions.
Avec la cache il nous est possible d'améliorer la vitesse d'accès à une donnée si une même donnée est demandée beaucoup de fois dans un court lapse de temps. Ici nous avons un texte qui ne change pas, il n'est donc pas nécessaire de vérifier s'il se trouve sur le disque à chaque requête. On peut considéer que la ressource est inchangée pour lapse de temps relativement long. Il nous est donc possible de diminuer de beaucoup le temps de traiter toutes les requêtes lorsque beaucoup de client demande la même ressouce en même temps.
Nous avons calculé que le temps pour traiter 100 requêtes simultanées est 6 fois plus rapide avec la cache qu'avec le thread pool uniquement.

Si le temps de traitement de la données était très court et que beaucoup de requêtes différentes étaient générées la priorité à l'écriture viendraient empatir les accès des lecteurs sur la cache. Il faudrait alors procéder avec une système de priorité égale au lecteur et au rédacteur.
En terme de temps notre solution d'utiliser un temps de cache relativement long n'est pas compatible avec une ressourece qui viendraient à changer fréquement.

