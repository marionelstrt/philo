Competences acquises

Ce projet m’a permis d’apprendre les bases de la programmation concurrentielle. On utilise des threads pour exécuter plusieurs entités (les philosophes) en parallèle, ainsi que des mutex pour gérer l’accès aux ressources partagées (les fourchettes), et ainsi éviter les conflits et les comportements indéterminés.

L’objectif était de simuler le problème des philosophes, en evitant les data race, en prevenant les deadlocks. 

Chaque philosophe doit penser, manger et dormir, en accédant à deux fourchettes partagées avec ses voisins. La difficulté principale réside dans la synchronisation correcte des accès, tout en respectant les délais imposés par les paramètres du programme.

Ce projet m’a permis de développer une compréhension concrète des threads, des verrous (mutex) et des problèmes classiques de la concurrence.

**How to use**

Lancer le programme avec les arguments suivants :

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

number_of_philosophers : nombre de philosophes (et donc de fourchettes)

time_to_die : temps en millisecondes avant qu’un philosophe ne meure s’il ne mange pas

time_to_eat : temps que met un philosophe pour manger

time_to_sleep : temps que met un philosophe pour dormir

(optionnel) number_of_times_each_philosopher_must_eat : si precise, la simulation s'arrête quand tous les philosophes ont mangé ce nombre de fois
