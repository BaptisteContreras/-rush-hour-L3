# Rush hour 


## Pour build :

  On utilise un CmakeList
  dans le Cmakelist.txt, il faut changer la ligne 4 (set(MY_SOURCE_DIR /home/baptiste/lyon1/rush-hour-etu/src)) et changer le chemin vers le dossier src.
  
####  Deux solutions pour le build :

    Utiliser Clion (conseillé)
ou
  - Via une invite de commande
  - Se rendre dans le dossier src
  - cmake CMakeLists.txt 
  - make
  - ./rush data/default.txt false false true
 
 Tout marche avec cette solution mais à la fin il y a une "Erreur de segmentation (core dumped)" alors que quand on le lance avec CLion on a aucun soucis.


# Pour éxecuter :

Il faut passer 4 arguments obligatoire :
executable [path] [test] [verb] [generation]

[path] = chemin vers le fichier à charger pour la résolution
[test] = lance les tests unitaires sur les mouvements (lorsqu'on met true, le programme éxecute que les tests et il ne fait pas de résolution)
[verb] = si true, le plateau pour chaque test unitaire est affiché
[generation] = si true, lance une nouvelle génération de terrain

(on ne peut pas lancer de résolution en même temps que les tests)
Si on veut changer le nombre de voiture pour la génération, il faut le faire dans le "main.cpp".

# Fuites de mémoires
Il y a une fuite de mémoire avec le Builder, il renvoit l'état initial qui sera stocké dans la class resolver. Dans les destructeurs de resolver on détruit l'état initial à la fin mais valgrind nous dis que l'état intial n'a pas été libéré alors que si.

Il y a quelques fuites de mémoire dans le générateur qu'on a pas réussi à résoudre.

Il y a aussi des fuite dans le parcour en largeur malgrès quelques optimisations





