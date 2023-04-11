# CPP_TERMINAL
Environnement Linux qui réplique un terminal programmé en C++
Travail réalisé dans le cadre d'un cours
Programme réalisé avec Léa MULLIEZ

Commande dispo :

  Commande BASH :
  - ls : afficher le contenu d’un répertoire
  - pwd : afficher le répertoire courant
  - man <nom de la commande> : afficher le manuel utilisateur de la commande
  - mkdir : créer un répertoire
  - rmdir : supprimer un répertoire
  - mv : déplacer un fichier
  - cat : concaténer et afficher à l’écran. Cette commande a plusieurs utilisés, je vous invite à utiliser man. Pour les besoins du laboratoire, cat affichera le contenu d’un fichier.

  Commande implémenté :
  - historique : Permet de voir les dernières commande envoyé par l'utilisateur.
  Exemple d'utilisation :
  Si vous avez, par exemple entré 110 commandes, alors les 100 dernières seront affichées 10 à 110. Même chose pour l’écran. Si vous entrez moins de 8 commandes alors elles sont numérotées 1 à 8, mais si vous enentrez 10 alors elles sont numérotées 3 à 10.
